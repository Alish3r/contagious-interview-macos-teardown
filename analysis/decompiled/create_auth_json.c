//========== create_auth_json  @ 10001b0ec

/* WARNING: Removing unreachable block (ram,0x00010001bbb4) */
/* WARNING: Removing unreachable block (ram,0x00010001bb9c) */
/* WARNING: Removing unreachable block (ram,0x00010001bbcc) */
/* WARNING: Removing unreachable block (ram,0x00010001bb84) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cloudsync_impl::create_auth_json(std::string const&, std::string const&) */

void __thiscall
cloudsync_impl::create_auth_json(cloudsync_impl *this,string *param_1,string *param_2)

{
  ulong uVar1;
  undefined *puVar2;
  ulong uVar3;
  size_t sVar4;
  string *psVar5;
  char ****ppppcVar6;
  string sVar7;
  undefined *puVar8;
  undefined *puVar9;
  byte bVar10;
  byte bVar11;
  undefined8 ****ppppuVar12;
  undefined8 *puVar13;
  size_t sVar14;
  ostream *poVar15;
  time_t tVar16;
  ushort uVar17;
  undefined8 **ppuVar18;
  char ***local_268 [2];
  undefined7 local_258;
  char cStack_251;
  char ***local_250 [2];
  undefined7 local_240;
  char cStack_239;
  undefined8 ***local_238;
  undefined *local_230;
  ulong local_228;
  void *local_1f0;
  undefined8 uStack_1e8;
  ulong local_1e0;
  undefined8 uStack_1d8;
  undefined4 local_1d0;
  undefined *local_1c8 [3];
  undefined8 uStack_1b0;
  undefined4 auStack_1a8 [30];
  char ***local_130;
  ulong uStack_128;
  undefined8 local_120;
  undefined8 ***local_118 [2];
  undefined7 local_108;
  char cStack_101;
  char ***local_100;
  ulong uStack_f8;
  undefined8 local_f0;
  undefined8 ***local_e8;
  long lStack_e0;
  char cStack_d1;
  undefined8 ***local_d0;
  uint local_c8;
  undefined4 uStack_c4;
  byte bStack_b9;
  undefined8 ***local_b8;
  undefined4 local_b0;
  undefined4 uStack_ac;
  byte bStack_a1;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_1000f03a8;
  base64::encode((base64 *)this,param_1);
  generate_filler((cloudsync_impl *)0x20,0x40,(ulong)param_2);
  generate_filler((cloudsync_impl *)0x20,0x40,(ulong)param_2);
  bVar11 = bStack_a1;
  bVar10 = bStack_b9;
  sVar14 = CONCAT44(uStack_c4,local_c8);
  if (-1 < (char)bStack_b9) {
    sVar14 = (ulong)bStack_b9;
  }
  sVar4 = CONCAT44(uStack_ac,local_b0);
  if (-1 < (char)bStack_a1) {
    sVar4 = (ulong)bStack_a1;
  }
  uVar3 = sVar4 + sVar14;
  if (0x7fffffffffffffef < uVar3) {
                    /* WARNING: Subroutine does not return */
    std::string::__throw_length_error_abi_v160006_();
  }
  if (uVar3 < 0x17) {
    local_230 = (undefined *)0x0;
    local_238 = (undefined8 ****)0x0;
    ppppuVar12 = &local_238;
    local_228 = uVar3 << 0x38;
  }
  else {
    uVar1 = (uVar3 | 0xf) + 1;
    ppppuVar12 = (undefined8 ****)operator_new(uVar1);
    local_228 = uVar1 | 0x8000000000000000;
    local_238 = ppppuVar12;
    local_230 = (undefined *)uVar3;
  }
  if (-1 < (char)bVar10) {
    local_d0 = &local_d0;
  }
  _memmove(ppppuVar12,local_d0,sVar14);
  if (-1 < (char)bVar11) {
    local_b8 = &local_b8;
  }
  _memmove((void *)((long)ppppuVar12 + sVar14),local_b8,sVar4);
  *(undefined1 *)((long)((long)ppppuVar12 + sVar14) + sVar4) = 0;
  if (-1 < (long)cStack_d1) {
    local_e8 = &local_e8;
  }
  if (-1 < cStack_d1) {
    lStack_e0 = (long)cStack_d1;
  }
  uVar17 = (ushort)lStack_e0;
  puVar13 = (undefined8 *)std::string::append((char *)&local_238,(ulong)local_e8);
  uStack_f8 = puVar13[1];
  local_100 = (char ***)*puVar13;
  local_f0 = puVar13[2];
  puVar13[1] = 0;
  puVar13[2] = 0;
  *puVar13 = 0;
  if ((long)local_228 < 0) {
    operator_delete(local_238,local_228 & 0x7fffffffffffffff);
  }
  if (-1 < (char)bStack_b9) {
    local_c8 = (uint)bStack_b9;
  }
  if (-1 < (char)bStack_a1) {
    local_b0._0_2_ = (ushort)bStack_a1;
  }
  zwc::encode_range((zwc *)(ulong)(local_c8 & 0xffff),(ushort)local_b0,uVar17);
  magic::encode();
  ppppuVar12 = (undefined8 ****)local_118[0];
  if (-1 < cStack_101) {
    ppppuVar12 = local_118;
  }
  puVar13 = (undefined8 *)std::string::append((char *)&local_238,(ulong)ppppuVar12);
  uStack_128 = puVar13[1];
  local_130 = (char ***)*puVar13;
  local_120 = puVar13[2];
  puVar13[1] = 0;
  puVar13[2] = 0;
  *puVar13 = 0;
  if ((long)local_228 < 0) {
    operator_delete(local_238,local_228 & 0x7fffffffffffffff);
  }
  puVar9 = PTR_vtable_1000f02f0;
  puVar8 = PTR_VTT_1000f02d8;
  puVar2 = PTR_vtable_1000f02f0 + 0x40;
  local_238 = *(undefined8 ****)(PTR_VTT_1000f02d8 + 8);
  local_1c8[0] = puVar2;
  *(undefined8 *)((long)&local_238 + (long)local_238[-3]) =
       *(undefined8 *)(PTR_VTT_1000f02d8 + 0x10);
  ppuVar18 = local_238[-3];
  std::ios_base::init((void *)((long)&local_238 + (long)ppuVar18));
  *(undefined8 *)((long)&uStack_1b0 + (long)ppuVar18) = 0;
  *(undefined4 *)((long)auStack_1a8 + (long)ppuVar18) = 0xffffffff;
  local_238 = (undefined8 ***)(puVar9 + 0x18);
  local_1c8[0] = puVar2;
  std::streambuf::streambuf((streambuf *)&local_230);
  puVar2 = PTR_vtable_1000f02e8;
  local_230 = PTR_vtable_1000f02e8 + 0x10;
  uStack_1e8 = 0;
  local_1f0 = (void *)0x0;
  uStack_1d8 = 0;
  local_1e0 = 0;
  local_1d0 = 0x10;
  uStack_98 = _UNK_10002b728;
  local_a0 = _DAT_10002b720;
  local_90 = 2;
  sobf::CTEnc<3ul>::str();
  ppppcVar6 = (char ****)local_250[0];
  if (-1 < cStack_239) {
