
@call envsetup.cmd
@call bVersion.cmd %1

@if "%QR_BUILD_TYPE%"=="" (
@set QR_BUILD_TYPE=Release
)

@if "%QR_PRODUCT_MODEL%"=="" (
@set QR_PRODUCT_MODEL=QR100
)

@if "%QR_BUILD_TARGET%"=="" (
@set QR_BUILD_TARGET=APP
)

@if "%QR_CUSTOMER_NAME%"=="" (
@set QR_CUSTOMER_NAME=ums
)

:: Create the out dir
cmake -E make_directory out

:: Enter into the out dir and cmake
cd out
cmake -DCMAKE_QR_BUILD_TYPE=%QR_BUILD_TYPE% -DCMAKE_TOOLCHAIN_FILE=../etc/toolchain.cmake -G "CodeBlocks - Unix Makefiles" -DBUILD_TARGET=%QR_BUILD_TARGET% -DPRODUCT_MODEL=%QR_PRODUCT_MODEL% -DAPP_NAME=%APP_NAME% -DCUSTOMER_NAME=%QR_CUSTOMER_NAME% -DCUSTOMER_SUBNAME=%QR_CUSTOMER_SUBNAME% ..
cd ..

:: Build target
cmake --build out -- -j4
:: VERBOSE=1

@echo.
@echo ==============================
@echo     Model: %QR_PRODUCT_MODEL%
@echo      Type: %QR_BUILD_TYPE%
@echo    Target: %QR_BUILD_TARGET%
@echo  Customer: %QR_CUSTOMER_NAME%
@echo   Version: %APP_VERSION%
@echo.

::@pause

