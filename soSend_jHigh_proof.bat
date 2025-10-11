
:: i need to use an absolute path, unless i can set this script directory as the working path like i do in bash.
:: im sure there is a way, ill find it later

SET projName=PROJ_NAME
SET modName=MOD_NAME

copy C:\Users\jacob\workspace\jHigh\%projName%\lib\%modName%.so C:\Users\jacob\workspace\jHigh\testEnv\lib\jHigh_proof\%modName%.so
