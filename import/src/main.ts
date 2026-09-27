import { mkdirSync, writeFileSync } from "fs";
import { type Charset } from "./charset.js";
import { blankChar, fullChar } from "./char.js";

function main() {
	const __dirname = import.meta.dirname;
	const generatedFolderPath = __dirname + "/../../generated";
	try {
		mkdirSync(generatedFolderPath, { recursive: true });
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
}

main();
