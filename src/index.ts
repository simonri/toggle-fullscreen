import { join } from "path";
const lib: AddonExports = require("node-gyp-build")(join(__dirname, ".."));

interface AddonExports {
  toggleFullscreen(title: string): void;
}

declare interface ToggleFullscreen {}

class ToggleFullscreen {
  toggleFullscreen(title: string) {
    lib.toggleFullscreen(title);
  }
}

export const toggleFullscreen = new ToggleFullscreen();
