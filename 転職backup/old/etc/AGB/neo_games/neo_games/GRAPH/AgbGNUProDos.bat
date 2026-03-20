@ECHO OFF

REM
REM    エラーについて
REM
REM もし「環境変数のための領域が足りません.」
REM というメッセージが出た場合は、このファイルを右クリックし、
REM 「メモリ」の「環境変数の初期サイズ」を 4096 にしてください。
REM
REM
REM    設定について
REM
REM
REM 以下のAGBDIR は、AGB の各ツールをインストールしたフォルダを
REM 記述してください。
REM
REM CYGNUSDIR は Cygnus の各ツールをインストールしたフォルダを
REM 記述してください。
REM

SET AGBDIR=C:/agb
SET CYGNUSDIR=C:/PROGRA~1/Cygnus
SET HOME=%AGBDIR%
SET MAKE_MODE=UNIX

REM 正常に動作している場合は以下の２行の先頭に REM を付けて
REM コメントにしてください

ECHO もしも正常に動作しない場合はこのファイルをテキストエディタで開き、
ECHO ファイル内の説明を参考に設定してください。

SET PATH=.;%CYGNUSDIR%/thumbelf-000512/H-i686-cygwin32/bin;%CYGNUSDIR%/native-99r1/H-i686-cygwin32/bin;%AGBDIR%/bin;C:\Windows;C:\Windows\Command

doskey.com
command.com
