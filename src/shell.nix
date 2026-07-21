{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  packages = with pkgs; [
    gcc
    clang-tools # includes clangd and clang-format
    gdb
    pkg-config
    codecrafters-cli
    cmake
  ];

  shellHook = ''
    echo "    It's C time :)"
  '';
}
