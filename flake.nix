{
  description = "A dev shell for kallgraph";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";

    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        llvm = pkgs.llvmPackages_14;
        IRDumper = pkgs.callPackage ./mlta/default.nix { inherit llvm; };
      in
      with pkgs;
      {
        devShells.default =
          (mkShell.override { stdenv = llvm.stdenv; }) {
            IRDumperPath = "${IRDumper}/lib/libDumper.so";
            buildInputs = [ pkgs.bashInteractive ];
            packages = (with pkgs; [
              llvm.clang
              llvm.libclang
              llvm.libllvm
              gnumake
              cmake
              ccache
              pkg-config
              (z3.dev)
              (z3.lib)
              (callPackage ./SVF-2.5/default.nix {
                inherit llvm;
              })
            ]);
          };
        formatter = nixpkgs-fmt;
      }
    );
}
