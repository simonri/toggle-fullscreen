import addon from "bindings";
const lib: AddonExports = addon("addon.node");

interface AddonExports {
  toggleFullscreen(title: string): void;
}

class ToggleFullscreen {
  toggleFullscreen(title: string) {
    lib.toggleFullscreen(title);
  }
}

export const toggleFullscreen = new ToggleFullscreen();
