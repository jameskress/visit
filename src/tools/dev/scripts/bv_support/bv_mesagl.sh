function bv_mesagl_initialize
{
    export DO_MESAGL="no"
}

function bv_mesagl_enable
{
    DO_MESAGL="yes"
    bv_glu_enable
}

function bv_mesagl_disable
{
    DO_MESAGL="no"
}

function bv_mesagl_depends_on
{
    echo "llvm"
}

function bv_mesagl_info
{
    export MESAGL_VERSION=${MESAGL_VERSION:-"17.3.9"}
    export MESAGL_FILE=${MESAGL_FILE:-"mesa-$MESAGL_VERSION.tar.xz"}
    export MESAGL_URL=${MESAGL_URL:-"https://archive.mesa3d.org/older-versions/17.x/"}
    export MESAGL_BUILD_DIR=${MESAGL_BUILD_DIR:-"mesa-$MESAGL_VERSION"}
    export MESAGL_MD5_CHECKSUM="b8042f9970ea70a36da1ee1fae27c448"
    export MESAGL_SHA256_CHECKSUM="c5beb5fc05f0e0c294fefe1a393ee118cb67e27a4dca417d77c297f7d4b6e479"
}

function bv_mesagl_print
{
    printf "%s%s\n" "MESAGL_FILE=" "${MESAGL_FILE}"
    printf "%s%s\n" "MESAGL_VERSION=" "${MESAGL_VERSION}"
    printf "%s%s\n" "MESAGL_BUILD_DIR=" "${MESAGL_BUILD_DIR}"
}

function bv_mesagl_print_usage
{
    printf "%-20s %s [%s]\n" "--mesagl" "Build MesaGL" "$DO_MESAGL"
}

function bv_mesagl_host_profile
{
    if [[ "$DO_MESAGL" == "yes" ]] ; then
        echo >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "## MesaGL" >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "VISIT_OPTION_DEFAULT(VISIT_MESAGL_DIR \${VISITHOME}/mesagl/$MESAGL_VERSION/\${VISITARCH})" >> $HOSTCONF
    fi
}

function bv_mesagl_selected
{
    args=$@
    if [[ $args == "--mesagl" ]]; then
        DO_MESAGL="yes"
        return 1
    fi

    return 0
}

function bv_mesagl_initialize_vars
{
    info "initalizing mesagl vars"
    if [[ "$DO_MESAGL" == "yes" ]]; then
        MESAGL_INSTALL_DIR="${VISITDIR}/mesagl/${MESAGL_VERSION}/${VISITARCH}"
        MESAGL_INCLUDE_DIR="${MESAGL_INSTALL_DIR}/include"
        MESAGL_LIB_DIR="${MESAGL_INSTALL_DIR}/lib"
        if [[ "$DO_STATIC_BUILD" == "yes" ]]; then
            MESAGL_OPENGL_LIB="${MESAGL_LIB_DIR}/libGL.a"
            MESAGL_OSMESA_LIB="${MESAGL_LIB_DIR}/libOSMesa.a"
            # initialized here, because glu's initialize_vars is called first
            # and install location won't be set properly for use with VTK
            MESAGL_GLU_LIB="${MESAGL_LIB_DIR}/libGLU.a"
        else
            MESAGL_OPENGL_LIB="${MESAGL_LIB_DIR}/libGL.${SO_EXT}"
            MESAGL_OSMESA_LIB="${MESAGL_LIB_DIR}/libOSMesa.${SO_EXT}"
            # initialized here, because glu's initialize_vars is called first
            # and install location won't be set properly for use with VTK
            MESAGL_GLU_LIB="${MESAGL_LIB_DIR}/libGLU.${SO_EXT}"
        fi
    fi
}

function bv_mesagl_ensure
{
    if [[ "$DO_DBIO_ONLY" != "yes" ]]; then
        if [[ "$DO_MESAGL" == "yes" ]] ; then
            ensure_built_or_ready "mesagl"   $MESAGL_VERSION   $MESAGL_BUILD_DIR   $MESAGL_FILE $MESAGL_URL
            if [[ $? != 0 ]] ; then
                return 1
            fi
        fi
    fi
}

function bv_mesagl_dry_run
{
    if [[ "$DO_MESAGL" == "yes" ]] ; then
        echo "Dry run option not set for mesagl."
    fi
}

function apply_mesagl_patch
{
    patch -p0 << \EOF
diff -c configure.ac.orig configure.ac
*** configure.ac.orig   Mon Jul 13 09:47:20 2020
--- configure.ac        Mon Jul 13 09:50:37 2020
***************
*** 2653,2659 ****
      dnl ourselves.
      dnl (See https://llvm.org/bugs/show_bug.cgi?id=6823)
      dnl We can't use $LLVM_VERSION because it has 'svn' stripped out,
!     LLVM_SO_NAME=LLVM-`$LLVM_CONFIG --version`
      AS_IF([test -f "$LLVM_LIBDIR/lib$LLVM_SO_NAME.$IMP_LIB_EXT"], [llvm_have_one_so=yes])

      if test "x$llvm_have_one_so" = xyes; then
--- 2653,2659 ----
      dnl ourselves.
      dnl (See https://llvm.org/bugs/show_bug.cgi?id=6823)
      dnl We can't use $LLVM_VERSION because it has 'svn' stripped out,
!     LLVM_SO_NAME=LLVM-$LLVM_VERSION
      AS_IF([test -f "$LLVM_LIBDIR/lib$LLVM_SO_NAME.$IMP_LIB_EXT"], [llvm_have_one_so=yes])

      if test "x$llvm_have_one_so" = xyes; then
EOF
    if [[ $? != 0 ]] ; then
        warn "MesaGL patch 1 failed."
        return 1
    fi

    #
    # Patch so that displaying graphics to the XWin-32 2018 X server
    # works properly.
    #
    patch -p0 << \EOF
diff -c src/gallium/winsys/sw/xlib/xlib_sw_winsys.c.orig src/gallium/winsys/sw/xlib/xlib_sw_winsys.c
*** src/gallium/winsys/sw/xlib/xlib_sw_winsys.c.orig	Thu Mar  4 13:12:20 2021
--- src/gallium/winsys/sw/xlib/xlib_sw_winsys.c	Thu Mar  4 13:14:11 2021
***************
*** 396,401 ****
--- 396,402 ----
  {
     struct xlib_displaytarget *xlib_dt;
     unsigned nblocksy, size;
+    int ignore;
  
     xlib_dt = CALLOC_STRUCT(xlib_displaytarget);
     if (!xlib_dt)
***************
*** 410,416 ****
     xlib_dt->stride = align(util_format_get_stride(format, width), alignment);
     size = xlib_dt->stride * nblocksy;
  
!    if (!debug_get_option_xlib_no_shm()) {
        xlib_dt->data = alloc_shm(xlib_dt, size);
        if (xlib_dt->data) {
           xlib_dt->shm = True;
--- 411,418 ----
     xlib_dt->stride = align(util_format_get_stride(format, width), alignment);
     size = xlib_dt->stride * nblocksy;
  
!    if (!debug_get_option_xlib_no_shm() &&
!        XQueryExtension(xlib_dt->display, "MIT-SHM", &ignore, &ignore, &ignore)) {
        xlib_dt->data = alloc_shm(xlib_dt, size);
        if (xlib_dt->data) {
           xlib_dt->shm = True;
EOF
    if [[ $? != 0 ]] ; then
        warn "MesaGL patch 2 failed."
        return 1
    fi

    return 0;
}

function build_mesagl
{
    #
    # prepare build dir
    #
    prepare_build_dir $MESAGL_BUILD_DIR $MESAGL_FILE
    untarred_mesagl=$?
    if [[ $untarred_mesagl == -1 ]] ; then
        warn "Unable to prepare MesaGL build directory. Giving Up!"
        return 1
    fi

    #
    # Apply patches
    #
    cd $MESAGL_BUILD_DIR || error "Couldn't cd to mesagl build dir."

    info "Patching MesaGL"
    apply_mesagl_patch
    if [[ $? != 0 ]] ; then
        if [[ $untarred_mesagl == 1 ]] ; then
            warn "Giving up on MesaGL build because the patch failed."
            return 1
        else
            warn "Patch failed, but continuing.  I believe that this script\n" \
                 "tried to apply a patch to an existing directory that had\n" \
                 "already been patched ... that is, the patch is\n" \
                 "failing harmlessly on a second application."
        fi
    fi

    #
    # Build MESAGL.
    #
    if [[ "$DO_STATIC_BUILD" == "yes" ]]; then
        MESAGL_STATIC_DYNAMIC="--disable-shared --disable-shared-glapi --enable-static --enable-static-glapi"
    fi
    if [[ "$VISIT_BUILD_MODE" == "Debug" ]]; then
        MESAGL_DEBUG_BUILD="--enable-debug"
    fi
    if [[ "$(uname -m)" == "x86_64" ]] ; then
        MESAGL_GALLIUM_DRIVERS="swrast,swr"
    else
        MESAGL_GALLIUM_DRIVERS="swrast"
    fi

    info "Configuring MesaGL . . ."
    echo CXXFLAGS="${CXXFLAGS} ${CXX_OPT_FLAGS}" \
        CXX=${CXX_COMPILER} \
        CFLAGS="${CFLAGS} ${C_OPT_FLAGS}" \
        CC=${C_COMPILER} \
        ./autogen.sh \
        --prefix=${VISITDIR}/mesagl/${MESAGL_VERSION}/${VISITARCH} \
        --with-platforms=x11 \
        --disable-dri \
        --disable-dri3 \
        --disable-egl \
        --disable-gbm \
        --disable-gles1 \
        --disable-gles2 \
        --disable-xvmc \
        --disable-vdpau \
        --disable-va \
        --enable-glx \
        --enable-llvm \
        --with-gallium-drivers=${MESAGL_GALLIUM_DRIVERS} \
        --enable-gallium-osmesa $MESAGL_STATIC_DYNAMIC $MESAGL_DEBUG_BUILD \
        --disable-llvm-shared-libs \
        --with-llvm-prefix=${VISIT_LLVM_DIR}
    env CXXFLAGS="${CXXFLAGS} ${CXX_OPT_FLAGS}" \
        CXX=${CXX_COMPILER} \
        CFLAGS="${CFLAGS} ${C_OPT_FLAGS}" \
        CC=${C_COMPILER} \
        ./autogen.sh \
        --prefix=${VISITDIR}/mesagl/${MESAGL_VERSION}/${VISITARCH} \
        --with-platforms=x11 \
        --disable-dri \
        --disable-dri3 \
        --disable-egl \
        --disable-gbm \
        --disable-gles1 \
        --disable-gles2 \
        --disable-xvmc \
        --disable-vdpau \
        --disable-va \
        --enable-glx \
        --enable-llvm \
        --with-gallium-drivers=${MESAGL_GALLIUM_DRIVERS} \
        --enable-gallium-osmesa $MESAGL_STATIC_DYNAMIC $MESAGL_DEBUG_BUILD \
        --disable-llvm-shared-libs \
        --with-llvm-prefix=${VISIT_LLVM_DIR}

    if [[ $? != 0 ]] ; then
        warn "MesaGL configure failed.  Giving up"
        return 1
    fi

    info "Building MesaGL . . ."
    ${MAKE} ${MAKE_OPT_FLAGS}
    if [[ $? != 0 ]] ; then
        warn "MesaGL build failed.  Giving up"
        return 1
    fi

    info "Installing MesaGL ..."
    ${MAKE} ${MAKE_OPT_FLAGS} install
    if [[ $? != 0 ]] ; then
        warn "MesaGL install failed.  Giving up"
        return 1
    fi

    if [[ "$DO_GROUP" == "yes" ]] ; then
        chmod -R ug+w,a+rX "$VISITDIR/mesagl"
        chgrp -R ${GROUP} "$VISITDIR/mesagl"
    fi
    cd "$START_DIR"
    info "Done with MesaGL"
    return 0
}

function bv_mesagl_is_enabled
{
    if [[ $DO_MESAGL == "yes" ]]; then
        return 1    
    fi
    return 0
}

function bv_mesagl_is_installed
{
    check_if_installed "mesagl" $MESAGL_VERSION
    if [[ $? == 0 ]] ; then
        return 1
    fi
    return 0
}

function bv_mesagl_build
{
    #
    # Build MesaGL
    #
    cd "$START_DIR"
    if [[ "$DO_MESAGL" == "yes" ]] ; then
        check_if_installed "mesagl" $MESAGL_VERSION
        if [[ $? == 0 ]] ; then
            info "Skipping MesaGL build.  MesaGL is already installed."
        else
            info "Building MesaGL (~20 minutes)"
            build_mesagl
            if [[ $? != 0 ]] ; then
                error "Unable to build or install MesaGL.  Bailing out."
            fi
            info "Done building MesaGL"
        fi
    fi
}
