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
    writeShellApplication
    {
      name = "build";
      nativeBuildInputs = [ pkgs.gcc ];
      text = "gcc build -g -Wall -Wextra -fsanitize=address -o shell";
    }

  ];

  shellHook = ''
    echo "    It's C time :)"
  '';
}
