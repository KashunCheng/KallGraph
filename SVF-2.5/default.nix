{ cmake
, llvm
, z3
,
}:
llvm.stdenv.mkDerivation {
  pname = "svf";
  version = "2.5";
  nativeBuildInputs = [ cmake ];
  buildInputs = [ llvm.llvm z3.dev z3.lib ];
  src = ./.;

  patchPhase = ''
    substituteInPlace include/Util/ExtAPI.h \
      --replace-fail '#define EXTAPI_JSON_PATH "/include/Util/ExtAPI.json"' \
                     "#define EXTAPI_JSON_PATH \"$out/include/Util/ExtAPI.json\""
  '';
}
