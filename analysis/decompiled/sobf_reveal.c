//========== reveal  @ 10001ce44

/* cloudsync_impl::sobf::reveal(unsigned char const*, unsigned long, unsigned long) */

void __thiscall cloudsync_impl::sobf::reveal(sobf *this,uchar *param_1,ulong param_2,ulong param_3)

{
  undefined8 *puVar1;
  byte bVar2;
  undefined *puVar3;
  undefined8 *in_x8;
  uchar *puVar4;
  long lVar5;
  
  *in_x8 = 0;
  in_x8[1] = 0;
  in_x8[2] = 0;
  if (param_1 != (uchar *)0x0) {
    std::string::append((ulong)in_x8,(char)param_1);
    puVar3 = PTR_K_1000f00f8;
    puVar4 = (uchar *)0x0;
    lVar5 = param_2 * 0x83;
    bVar2 = PTR_K_1000f00f8[param_2 & 0x1f];
    do {
      puVar1 = (undefined8 *)*in_x8;
      if (-1 < *(char *)((long)in_x8 + 0x17)) {
        puVar1 = in_x8;
      }
      *(byte *)((long)puVar1 + (long)puVar4) =
           (byte)this[(long)puVar4] ^ (byte)lVar5 ^ bVar2 ^ puVar3[(ulong)puVar4 & 0x1f];
      puVar4 = puVar4 + 1;
      lVar5 = lVar5 + 0x11;
    } while (param_1 != puVar4);
    return;
  }
  return;
}

