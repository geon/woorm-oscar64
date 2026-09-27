import { type Char, charEquals } from "./char.js";

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
		throw new Error("Charset full.");
	}
	charset.push(char);
	return charset.length - 1;
}

export function charsetCompress(
	charset: Charset,
	usedChars: Set<number>,
	initial: Charset,
): {
	mappingTable: number[];
	compressedCharset: Charset;
} {
	const mappingTable: number[] = [];
	const compressedCharset: MutableCharset = [...initial];

	for (let [index, char] of [...charset.entries()].filter(([index]) =>
		usedChars.has(index),
	)) {
		mappingTable[index] = charsetFindIndexOrAdd(compressedCharset, char);
	}

	return {
		mappingTable,
		compressedCharset,
	};
}
