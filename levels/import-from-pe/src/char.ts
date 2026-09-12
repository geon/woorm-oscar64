export type Char = readonly number[];

export function charEquals(a: Char, b: Char): boolean {
	for (let i = 0; i < 8; ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

// export function charHasBg12Colors(char: Char): boolean {
// 	// Check all lines.
// 	for (let i = 0; i < 8; ++i) {
// 		let line = char[i];
// 		if (line === undefined) {
// 			throw new Error("Missing line.");
// 		}

// 		// Check all bit-pairs.
// 		for (let j = 0; j < 4; ++j) {
// 			let bitPair = (line >> (j * 2)) & 0b11;

// 			if (bitPair == 0b10 || bitPair == 0b11) {
// 				return true;
// 			}
// 		}
// 	}

// 	return false;
// }

export function multiColorCharHasPrimaryColor(char: Char): boolean {
	// Check all lines.
	for (let i = 0; i < 8; ++i) {
		let line = char[i];
		if (line === undefined) {
			throw new Error("Missing line.");
		}

		// Check all bit-pairs.
		for (let j = 0; j < 4; ++j) {
			let bitPair = (line >> (j * 2)) & 0b11;

			if (bitPair == 0b11) {
				return true;
			}
		}
	}

	return false;
}
