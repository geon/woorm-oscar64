import { mkdirSync, writeFileSync } from "fs";
import { importLevels } from "./import-levels.js";
import { type Charset } from "./charset.js";
import { blankChar, fullChar } from "./char.js";

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
		fullChar,
	];

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
