import { multiColorCharHasPrimaryColor } from "./char.js";
import { charsetCompress } from "./charset.js";
import type { Level } from "./Level.js";

export function optimizeLevel(level: Level): Level {
	const compressed = charsetCompress(level);
	if (!compressed) {
		throw new Error("Failed to compress charset.");
	}
	const { compressedCharset, mappingTable } = compressed;

	return {
		...level,
		colors: removeInvisibleColorChanges(level),
		chars: remapChars(level.chars, mappingTable),
		charset: compressedCharset,
	};
}

function remapChars(
	levelChars: Level["chars"],
	mappingTable: readonly number[],
): Level["chars"] {
	return levelChars.map((x) => {
		const mapped = mappingTable[x];
		if (mapped === undefined) {
			throw new Error("Missing mapping.");
		}
		return mapped;
	});
}

function removeInvisibleColorChanges(level: Level): Level["colors"] {
	const noMultiPrimaryColorChars = new Set(
		[...level.charset.entries()]
			.filter(([_, char]) => !multiColorCharHasPrimaryColor(char))
			.map(([index]) => index),
	);

	let lastColor = level.colors[0]!;
	return [...level.colors.entries()].map(([index, color]) => {
		if (color > 7 && noMultiPrimaryColorChars.has(level.chars[index]!)) {
			return lastColor;
		}

		lastColor = color;
		return color;
	});
}
