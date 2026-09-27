import { readFileSync } from "fs";
import { deserializePeFileData } from "./pe/pe-file.js";
import { peFileDataToLevels } from "./level-pe-conversion.js";
import { optimizeLevel } from "./optimize-level.js";
import type { Level } from "./Level.js";
import type { Charset } from "./charset.js";

function getLevelCCode(
	level: Level,
): string | NodeJS.ArrayBufferView<ArrayBufferLike> {
	const levelFileName = getLevelFileName(level);

	const playerStarts = level.playerStarts
		.map(
			(playerStart) =>
				`		{{${playerStart.position.x}, ${playerStart.position.y}}, ${playerStart.direction}},`,
		)
		.join("\n");

	return `
char level_${levelFileName}_title[] = "Title";

uint8_t level_${levelFileName}_chars[] = {
#embed lzo "${levelFileName}_chars.bin"
};
uint8_t level_${levelFileName}_colors[] = {
#embed lzo "${levelFileName}_colors.bin"
};
uint8_t level_${levelFileName}_charset[] = {
#embed lzo "${levelFileName}_charset.bin"
};

const Level level_${levelFileName} = {
	level_${levelFileName}_title,
	${level.multiColor1},
	${level.multiColor2},
	{
${playerStarts}
	},
	level_${levelFileName}_chars,
	level_${levelFileName}_colors,
	level_${levelFileName}_charset,
};
`;
}

function getLevelBins(level: Level, staticCharset: Charset) {
	const optimized = optimizeLevel(level, staticCharset);
	const levelFileName = getLevelFileName(level);
	return [
		{
			name: `${levelFileName}_chars.bin`,
			content: new Uint8Array(optimized.chars.flat()),
		},
		{
			name: `${levelFileName}_colors.bin`,
			content: new Uint8Array(optimized.colors.flat()),
		},
		{
			name: `${levelFileName}_charset.bin`,
			content: new Uint8Array(optimized.charset.flat()),
		},
	];
}

function getLevelFileName(level: Level): string {
	return level.name.toLowerCase().replaceAll(" ", "_").replaceAll("&", "n");
}

export function importLevels(peFilePath: string, staticCharset: Charset) {
	const levels = peFileDataToLevels(
		deserializePeFileData(
			readFileSync(peFilePath, {
				encoding: "utf-8",
			}),
		),
	);

	const generatedFiles = levels.flatMap((level) =>
		getLevelBins(level, staticCharset),
	);

	generatedFiles.push({
		name: "levels.h",
		content: new TextEncoder().encode(`
#ifndef LEVELS_H
#define LEVELS_H

#include "../../src/level.h"

extern const Level *levels[];

#define NUM_LEVELS ${levels.length - 1}

#endif
		`),
	});

	generatedFiles.push({
		name: "levels.c",
		content: new TextEncoder().encode(`#include "../../src/level.h"

${levels.map(getLevelCCode).join("\n")}

const Level *levels[]  = {
${levels
	.map(getLevelFileName)
	.filter((name) => name !== "title_screen")
	.map((name) => `	&level_${name}`)
	.join(",\n")}
};
`),
	});

	return generatedFiles;
}
