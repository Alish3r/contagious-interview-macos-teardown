//========== cs_accept_server_trust @ 100028b34

/* cs_accept_server_trust(NSURLAuthenticationChallenge*, void (
   block_pointer)(NSURLSessionAuthChallengeDisposition, NSURLCredential*)) */

void cs_accept_server_trust
               (NSURLAuthenticationChallenge *param_1,
               _func_void_NSURLSessionAuthChallengeDisposition_NSURLCredential_ptr *param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long local_48;
  
  _objc_retain();
  _objc_retain(param_2);
  puVar1 = PTR_s_protectionSpace_1000f5960;
  _objc_msgSend(param_1,PTR_s_protectionSpace_1000f5960);
  uVar2 = _objc_retainAutoreleasedReturnValue();
  _objc_msgSend(uVar2,PTR_s_authenticationMethod_1000f5968);
  uVar3 = _objc_retainAutoreleasedReturnValue();
  uVar4 = _objc_msgSend(uVar3,PTR_s_isEqualToString__1000f5738,
                        *(undefined8 *)PTR__NSURLAuthenticationMethodServerTrust_1000f0070);
  _objc_release(uVar3);
  _objc_release(uVar2);
  if ((uVar4 & 1) == 0) {
    (**(code **)(param_2 + 0x10))(param_2,1,0);
  }
  else {
    _objc_msgSend(param_1,puVar1);
    uVar2 = _objc_retainAutoreleasedReturnValue();
    lVar5 = _objc_msgSend(uVar2,PTR_s_serverTrust_1000f5970);
    _objc_release(uVar2);
    if (lVar5 == 0) {
      (**(code **)(param_2 + 0x10))(param_2,2,0);
    }
    else {
      local_48 = 0;
      _SecTrustEvaluateWithError(lVar5,&local_48);
      if (local_48 != 0) {
        _CFRelease();
      }
      lVar6 = _SecTrustCopyExceptions(lVar5);
      if (lVar6 != 0) {
        _SecTrustSetExceptions(lVar5,lVar6);
        _CFRelease(lVar6);
      }
      _objc_msgSend(PTR__OBJC_CLASS___NSURLCredential_1000f5ab0,PTR_s_credentialForTrust__1000f5978,
                    lVar5);
      uVar2 = _objc_retainAutoreleasedReturnValue();
      (**(code **)(param_2 + 0x10))(param_2,0,uVar2);
      _objc_release(uVar2);
    }
  }
  _objc_release(param_2);
  _objc_release(param_1);
  return;
}


//========== cs_url_session_configuration @ 100028d44

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cs_url_session_configuration(double) */

void cs_url_session_configuration(double param_1)

{
  ulong uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 *****pppppuVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 ******ppppppuVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 *****local_178;
  ulong uStack_170;
  undefined7 local_168;
  char cStack_161;
  undefined8 *****local_160;
  ulong uStack_158;
  undefined8 local_150;
  undefined8 *****local_148;
  ulong uStack_140;
  undefined7 local_138;
  char cStack_131;
  undefined8 *****local_130;
  ulong uStack_128;
  undefined8 local_120;
  undefined8 *****local_118;
  ulong uStack_110;
  undefined7 local_108;
  char cStack_101;
  undefined8 *****local_100;
  ulong uStack_f8;
  undefined8 local_f0;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  long local_88;
  
  local_88 = *(long *)PTR____stack_chk_guard_1000f03a8;
  _objc_msgSend(PTR__OBJC_CLASS___NSURLSessionConfiguration_1000f5a88,
                PTR_s_ephemeralSessionConfiguration_1000f58f0);
  uVar5 = _objc_retainAutoreleasedReturnValue();
  if (param_1 == 0.0 || param_1 < 0.0 != NAN(param_1)) {
    param_1 = 600.0;
  }
  _objc_msgSend(param_1,uVar5,PTR_s_setTimeoutIntervalForRequest__1000f58f8);
  _objc_msgSend(0x4092c00000000000,uVar5,PTR_s_setTimeoutIntervalForResource__1000f5900);
  _objc_msgSend(uVar5,PTR_s_setRequestCachePolicy__1000f5908,1);
  _objc_msgSend(uVar5,PTR_s_setURLCache__1000f5910,0);
  _objc_msgSend(uVar5,PTR_s_setHTTPCookieStorage__1000f5918,0);
  _objc_msgSend(uVar5,PTR_s_setHTTPShouldSetCookies__1000f5920,0);
  _objc_msgSend(uVar5,PTR_s_setTLSMinimumSupportedProtocolVe_1000f5928,0x303);
  uStack_a8 = _UNK_1000eaf38;
  local_b0 = _DAT_1000eaf30;
  uStack_98 = _UNK_1000eaf48;
  uStack_a0 = _DAT_1000eaf40;
  cloudsync_impl::sobf::CTEnc<11ul>::str();
  pppppuVar4 = local_118;
  if (cStack_101 < '\0') {
