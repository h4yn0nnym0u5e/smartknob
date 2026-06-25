@echo off
REM protobuf generator using pre-compiled binary
REM using Python seems to be ridiculously difficult...
REM run using .\generate_protobuf at command prompt

SET GEN_PATH="D:\Jonathan\misc\apps\nanopb-0.4.9.1-windows-x86\generator-bin"
SET OUT_PATH="..\firmware\src\proto_gen"
%GEN_PATH%\nanopb_generator -D %OUT_PATH% -I . smartknob.proto 
