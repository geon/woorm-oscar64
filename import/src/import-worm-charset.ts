import { mkdirSync, readFileSync, writeFileSync } from "fs";
import { deserializePeFileData } from "./pe/pe-file";
import { charEquals, type Char } from "./char";
import { charsetCompress } from "./charset";

const placementLayout = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 3, 2, 1, 0, 3, 3, 3, 3, 0, 1, 2, 3],
	[1, 1, 1, 1, 3, 2, 1, 0, 2, 2, 2, 2, 0, 1, 2, 3],
	[2, 2, 2, 2, 3, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 3],
	[3, 3, 3, 3, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3],
	[1, 0, 1, 0, 1, 0, 1, 0, 2, 1, 2, 1, 2, 1, 2, 1],
	[2, 3, 2, 3, 2, 3, 2, 3, 3, 0, 3, 0, 3, 0, 3, 0],
	[3, 2, 3, 2, 3, 2, 3, 2, 0, 3, 0, 3, 0, 3, 0, 3],
	[0, 1, 0, 1, 0, 1, 0, 1, 1, 2, 1, 2, 1, 2, 1, 2],
	[1, 2, 1, 2, 1, 2, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3],
	[0, 3, 0, 3, 0, 3, 0, 3, 1, 0, 1, 0, 1, 0, 1, 0],
	[3, 0, 3, 0, 3, 0, 3, 0, 0, 1, 0, 1, 0, 1, 0, 1],
	[2, 1, 2, 1, 2, 1, 2, 1, 3, 2, 3, 2, 3, 2, 3, 2],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
].flat();

const lastDirectionLayout = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
	[3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2],
	[0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
	[3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2],
	[3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0],
	[2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1],
	[3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0],
	[2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
].flat();

const directionLayout = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3],
	[1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2],
	[0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3],
	[1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2],
	[0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3],
	[2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3],
	[1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0],
	[2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3],
	[1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
].flat();

const microStepLayout = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 1, 2, 3, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0],
	[0, 1, 2, 3, 1, 1, 1, 1, 0, 1, 2, 3, 1, 1, 1, 1],
	[0, 1, 2, 3, 2, 2, 2, 2, 0, 1, 2, 3, 2, 2, 2, 2],
	[0, 1, 2, 3, 3, 3, 3, 3, 0, 1, 2, 3, 3, 3, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
].flat();

const usedLayout = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
].flat();

// Must be identical to the C version.
function wormCharPackBits(
	placement: number,
	lastDirection: number,
	direction: number,
	microStep: number,
) {
	return (
		(0b11000000 & microStep) |
		(0b00110000 & (placement << 4)) |
		(0b00001100 & (lastDirection << 2)) |
		(0b00000011 & direction)
	);
}

function getCharsetLookup() {
	const charsetLookup = Array.from({ length: 256 }, () => 0);

	for (let index = 0; index < 256; ++index) {
		if (usedLayout[index]) {
			charsetLookup[
				wormCharPackBits(
					placementLayout[index]!,
					lastDirectionLayout[index]!,
					directionLayout[index]!,
					microStepLayout[index]! << 6,
				)
			] = index;
		}
	}

	return charsetLookup;
}

const blankChar: Char = [0, 0, 0, 0, 0, 0, 0, 0];

function getWormCharset() {
	const __dirname = import.meta.dirname;

	const peFileData = deserializePeFileData(
		readFileSync(__dirname + "/../../assets/worm-charset.pe", {
			encoding: "utf-8",
		}),
	);

	const unpackedWormCharset = peFileData.charsets[2]?.bitmaps;
	if (!unpackedWormCharset) {
		throw new Error("Missing worm charset.");
	}

	const usedChars = new Set(
		unpackedWormCharset
			.map((char, index) => ({ char, index }))
			.filter(({ char }) => !charEquals(char, blankChar))
			.map(({ index }) => index),
	);
	// For the empty tile.
	usedChars.add(0);

	const wormCharset = charsetCompress(unpackedWormCharset, usedChars);
	if (!wormCharset) {
		throw new Error("Failed to compress wormCharset.");
	}

	return wormCharset;
}

export function importWormCharset(): number {
	const __dirname = import.meta.dirname;
	const generatedFolderPath = __dirname + "/../../generated";

	try {
		mkdirSync(generatedFolderPath, { recursive: true });
	} catch (error: any) {
		if (error.code !== "EEXIST") throw error;
	}

	const wormCharset = getWormCharset();
	const charsetStaticSize = wormCharset.compressedCharset.length;
	const charsetLookup = getCharsetLookup().map(
		(target) => wormCharset.mappingTable[target]!,
	);

	writeFileSync(
		generatedFolderPath + `/worm-charset-lookup.bin`,
		new Uint8Array(charsetLookup),
	);

	writeFileSync(
		generatedFolderPath + `/charset.bin`,
		new Uint8Array(wormCharset.compressedCharset.flat()),
	);

	writeFileSync(
		generatedFolderPath + `/charset-static-size.h`,
		`
#define CHARSET_STATIC_SIZE ${charsetStaticSize}
		`,
	);

	// writeFileSync(
	// 	generatedFolderPath + `/charset.dec`,
	// 	wormCharset.compressedCharset.flat().join(","),
	// );

	return charsetStaticSize;
}
