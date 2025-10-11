
:: i need to use an absolute path, unless i can set this script directory as the working path like i do in bash.
:: im sure there is a way, ill find it later

SET projDir=PROJ_DIR
SET projName=PROJ_NAME
SET modName=MOD_NAME
SET testEnv_dir=C:\Users\jacob\workspace\jHigh\testEnv\

copy "%projDir%%projName%\lib\%modName%.so" "%testEnv_dir%lib\%modName%.so"
