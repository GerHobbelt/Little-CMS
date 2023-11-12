
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

extern int lcms2_demo_cmyk_main(void);
extern int lcms2_fast_float_testbed_main(void);
extern int lcms2_threaded_testbed_main(void);
extern int lcms2_alpha_test_main(void);
extern int lcms2_test_main(int argc, const char** argv);
extern int lcms2_jpgicc_util_main(int argc, const char** argv);
extern int lcms2_linkicc_util_main(int argc, const char** argv);
extern int lcms2_psicc_util_main(int argc, const char** argv);
//extern int lcms2_itufax_example_main(int argc, const char** argv);
//extern int lcms2_mkcmy_example_main(void);
//extern int lcms2_mkgrayer_example_main(int argc, const char** argv);
extern int lcms2_mktiff8_example_main(int argc, const char** argv);
extern int lcms2_roundtrip_example_main(int argc, const char** argv);
extern int lcms2_vericc_example_main(int argc, const char** argv);
extern int lcms2_wtpt_example_main(int argc, const char** argv);
extern int lcms2_tiffdiff_util_main(int argc, const char** argv);
extern int lcms2_tificc_util_main(int argc, const char** argv);
extern int lcms2_transicc_util_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
