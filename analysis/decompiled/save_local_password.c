//========== save_local_password  @ 10000eab8

/* cloudsync_impl::save_local_password(std::string const&, std::string const&) */

bool __thiscall
cloudsync_impl::save_local_password(cloudsync_impl *this,string *param_1,string *param_2)

{
  uint uVar1;
  char *****pppppcVar2;
  long lVar3;
  char ****local_2b8;
  ulong uStack_2b0;
  undefined7 local_2a8;
  char cStack_2a1;
  char ****local_2a0 [2];
  undefined7 local_290;
  char cStack_289;
  void *local_288 [2];
  undefined7 local_278;
  char cStack_271;
  long local_270;
  filebuf afStack_268 [24];
  uint auStack_250 [96];
  ios aiStack_d0 [152];
  long local_38;
  
  local_38 = *(long *)PTR____stack_chk_guard_1000f03a8;
  get_app_config_dir(param_1);
  get_auth_json_path(param_1);
  std::__fs::filesystem::__create_directories((path *)local_288,(error_code *)0x0);
  create_auth_json(this,param_1,param_2);
  pppppcVar2 = (char *****)local_2a0[0];
  if (-1 < cStack_289) {
    pppppcVar2 = local_2a0;
  }
  std::ofstream::ofstream((ofstream *)&local_270,(char *)pppppcVar2,0x10);
  uVar1 = *(uint *)((long)auStack_250 + *(long *)(local_270 + -0x18)) & 5;
  if (uVar1 == 0) {
    pppppcVar2 = (char *****)local_2b8;
    if (-1 < (long)cStack_2a1) {
      pppppcVar2 = &local_2b8;
    }
    if (-1 < cStack_2a1) {
      uStack_2b0 = (long)cStack_2a1;
    }
    std::__put_character_sequence_abi_v160006_<char,std::char_traits<char>>
              ((ostream *)&local_270,(char *)pppppcVar2,uStack_2b0);
    lVar3 = std::filebuf::close();
    if (lVar3 == 0) {
      std::ios_base::clear((int)&local_270 + (int)*(undefined8 *)(local_270 + -0x18));
    }
    pppppcVar2 = (char *****)local_2a0[0];
    if (-1 < cStack_289) {
      pppppcVar2 = local_2a0;
    }
    _chmod((char *)pppppcVar2,0x1a4);
  }
  local_270 = *(long *)PTR_VTT_1000f02d0;
  *(undefined8 *)(afStack_268 + *(long *)(local_270 + -0x18) + -8) =
       *(undefined8 *)(PTR_VTT_1000f02d0 + 0x18);
  std::filebuf::~filebuf(afStack_268);
  std::ostream::~ostream((ostream *)&local_270);
  std::ios::~ios(aiStack_d0);
  if (cStack_2a1 < '\0') {
    operator_delete(local_2b8,CONCAT17(cStack_2a1,local_2a8) & 0x7fffffffffffffff);
  }
  if (cStack_289 < '\0') {
    operator_delete(local_2a0[0],CONCAT17(cStack_289,local_290) & 0x7fffffffffffffff);
  }
  if (cStack_271 < '\0') {
    operator_delete(local_288[0],CONCAT17(cStack_271,local_278) & 0x7fffffffffffffff);
    if (*(long *)PTR____stack_chk_guard_1000f03a8 != local_38) goto LAB_10000eca4;
  }
  else if (*(long *)PTR____stack_chk_guard_1000f03a8 != local_38) {
LAB_10000eca4:
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return uVar1 == 0;
}

