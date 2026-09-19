import { multiColorCharHasPrimaryColor } from "./char.js";
import { charsetCompress } from "./charset.js";
import type { Level } from "./Level.js";

export function optimizeLevel(level: Level, charsetStaticSize: number): Level {
	const compressed = charsetCompress(level.charset, new Set(level.chars));
	if (!compressed) {
		throw new Error("Failed to compress charset.");
	}
	const { compressedCharset, mappingTable } = compressed;

	return {
		...level,
		colors: removeInvisibleColorChanges(level),
		chars: remapChars(
			level.chars,
			mappingTable.map((target) =>
				// Add the charsetStaticSize to the char index, so the per-level chars can be loaded after the static portion.
				// The zero-index means empty space, so must be preserved.
				target === 0 ? 0 : target + charsetStaticSize,
			),
		),
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
