import type { Charset } from "./charset.js";

export type Coord = {
	readonly x: number;
	readonly y: number;
};

export type PlayerStart = {
	readonly position: Coord;
	readonly direction: number;
};

export type Level = {
	readonly name: string;
	readonly multiColor1: number;
	readonly multiColor2: number;
	readonly playerStarts: readonly PlayerStart[];
	readonly chars: readonly number[];
	readonly colors: readonly number[];
	readonly charset: Charset;
};
