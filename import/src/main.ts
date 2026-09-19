import { mkdirSync, writeFileSync } from "fs";
import { importLevels } from "./import-levels.js";
import {
	getWormCharsetLookup,
	importWormCharset,
} from "./import-worm-charset.js";
import { charsetCompress, type Charset } from "./charset.js";
import { blankChar, charEquals } from "./char.js";

function main() {
	const __dirname = import.meta.dirname;
	const generatedFolderPath = __dirname + "/../../generated";
	const levelsFolderPath = generatedFolderPath + "/levels";
	try {
		mkdirSync(levelsFolderPath, { recursive: true });
	} catch (error: any) {
		if (error.code !== "EEXIST") throw error;
	}

	let staticCharset: Charset = [
		// blankChar must be at index 0 for collission detection.
		blankChar,
	];

	const unpackedWormCharset = importWormCharset();
	const usedCharsWorm = new Set(
		unpackedWormCharset
			.map((char, index) => ({ char, index }))
			.filter(({ char }) => !charEquals(char, blankChar))
			.map(({ index }) => index),
	);
	const wormCharset = charsetCompress(
		unpackedWormCharset,
		usedCharsWorm,
		staticCharset,
	);
	staticCharset = wormCharset.compressedCharset;

	const wormCharsetLookup = getWormCharsetLookup();

	writeFileSync(
		generatedFolderPath + `/worm-charset-lookup.bin`,
		new Uint8Array(
			wormCharsetLookup.map((target) => wormCharset.mappingTable[target]!),
		),
	);

	writeFileSync(
		generatedFolderPath + `/charset.bin`,
		new Uint8Array(staticCharset.flat()),
	);

	writeFileSync(
		generatedFolderPath + `/charset-static-size.h`,
		`#define CHARSET_STATIC_SIZE ${staticCharset.length}`,
	);

	for (const file of importLevels(
		__dirname + "/../../assets/levels.pe",
		staticCharset,
	)) {
		writeFileSync(`${levelsFolderPath}/${file.name}`, file.content);
	}
}

main();
