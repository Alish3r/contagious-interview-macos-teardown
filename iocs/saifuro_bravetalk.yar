rule Saifuro_BraveTalk_macOS_Stealer
{
    meta:
        description = "Fake 'Brave Talk' / Contagious-Interview macOS infostealer (cloudsync_impl)"
        reference   = "https://github.com/Alish3r/contagious-interview-macos-teardown"
        date        = "2026-11-03"
        tlp         = "WHITE"
        hash        = "782f21b0ce945931bab8b1d84dc57d542a510ec66b80f9034fefd04dcd53572b"
    strings:
        $ns1 = "cloudsync_impl" ascii
        $ns2 = "4sobf" ascii
        $f1  = "save_local_password" ascii
        $f2  = "create_auth_json" ascii
        $f3  = "APP_PROCESS_DISGUISE_NAME" ascii
        $f4  = "APP_OPS_CHACHA" ascii
        $f5  = "CSURLInsecureDelegate" ascii
        $f6  = "showPasswordDialog" ascii
        $z   = "zwc" ascii
    condition:
        (uint32(0) == 0xBEBAFECA or uint32(0) == 0xFEEDFACF or uint32(0) == 0xCFFAEDFE)
        and $ns1 and 4 of ($f*, $ns2, $z)
}
