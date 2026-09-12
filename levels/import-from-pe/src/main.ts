import { mkdirSync, readFileSync, writeFileSync } from "fs";
import { deserializePeFileData } from "./pe/pe-file.js";
import { peFileDataToLevels } from "./level-pe-conversion.js";
import { optimizeLevel } from "./optimize-level.js";
import type { Level } from "./Level.js";

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

function writeLevelBins(generatedFolderPath: string, level: Level) {
	const optimized = optimizeLevel(level);

	const levelFileName = getLevelFileName(level);

	writeFileSync(
		generatedFolderPath + `/${levelFileName}_chars.bin`,
		new Uint8Array(optimized.chars.flat()),
	);
	writeFileSync(
		generatedFolderPath + `/${levelFileName}_colors.bin`,
		new Uint8Array(optimized.colors.flat()),
	);
	writeFileSync(
		generatedFolderPath + `/${levelFileName}_charset.bin`,
		new Uint8Array(optimized.charset.flat()),
	);
}

function getLevelFileName(level: Level): string {
	return level.name.toLowerCase().replaceAll(" ", "_").replaceAll("&", "n");
}

function main() {
	const __dirname = import.meta.dirname;
	const generatedFolderPath = __dirname + "/../../generated";

	const levels = peFileDataToLevels(
		deserializePeFileData(
			readFileSync(__dirname + "/../../levels.pe", { encoding: "utf-8" }),
		),
	);

	try {
		mkdirSync(generatedFolderPath, { recursive: true });
	} catch (error: any) {
		if (error.code !== "EEXIST") throw error;
	}

	for (const level of levels) {
		writeLevelBins(generatedFolderPath, level);
	}

	writeFileSync(
		generatedFolderPath + "/levels.h",
		`
#ifndef LEVELS_H
#define LEVELS_H

#include "../../src/level.h"

extern const Level *levels[];

#define NUM_LEVELS ${levels.length - 1}

#endif
		`,
	);

	writeFileSync(
		generatedFolderPath + "/levels.c",
		`#include "../../src/level.h"

${levels.map(getLevelCCode).join("\n")}

const Level *levels[]  = {
${levels
	.map(getLevelFileName)
	.filter((name) => name !== "title_screen")
	.map((name) => `	&level_${name}`)
	.join(",\n")}
};
`,
	);
}

main();
