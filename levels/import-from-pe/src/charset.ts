import { type Char, charEquals } from "./char.js";
import type { Level } from "./Level.js";

export type Charset = readonly Char[];
export type MutableCharset = Char[];

function charsetFindIndexOrAdd(charset: MutableCharset, char: Char): number {
	// Avoid adding duplicates.
	const index = charset.findIndex((x) => {
		return charEquals(x, char);
	});
	if (index != -1) {
		return index;
	}

	// New unique char, so add it if not full.
	if (charset.length >= 256) {
		// Charset is full
		return -1;
	}
	charset.push(char);
	return charset.length - 1;
}

export function charsetCompress(level: Level):
	| {
			mappingTable: number[];
			compressedCharset: Charset;
	  }
	| undefined {
	const usedChars = new Set(level.chars);

	const mappingTable: number[] = [];
	const compressedCharset: MutableCharset = [];

	for (let [index, char] of [...level.charset.entries()].filter(([index]) =>
		usedChars.has(index),
	)) {
		const resultingIndex = charsetFindIndexOrAdd(compressedCharset, char);
		if (resultingIndex == -1) {
			return undefined;
		}

		mappingTable[index] = resultingIndex;
	}

	return {
		mappingTable,
		compressedCharset,
	};
}

//  function charsetAddNewCharsUsedInLevel(Charset: Charset , levelCharset: Charset , chars[1000]: number ): void
// {
// 	for (int i = 0; i < 1000; ++i)
// 	{
// 		CharsetFindIndexOrAdd(Charset, levelCharset[chars[i]]);
// 	}
// }
