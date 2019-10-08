
@call envsetup.cmd

@cmake --build out --target clean
@rm -rf out
@rm -rf target_image_name.cmd
@rm -rf upd.tmp

::@pause

