/**
* @file 		MD_RTU_User_Fun.c
* @brief		无
* @details	无
* @author		zspace
* @date		2020/3/23
* @version	A001
* @par History:  无       
*/
#include "MD_RTU_User_Fun.h"
#include "MD_RTU_Fun.h"

/*读取bits,可以读取一个，也可以读取多个*/
BOOL MDS_RTU_ReadBits(void* obj,uint16 modbusAddr,uint16 numOf, uint8 *res, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	/*只能操作bits*/
	if(opAddrType != COILS_TYPE && opAddrType != INPUT_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+numOf)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType==opAddrType){/*指定类型*/
				uint16 	j;
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				for(j=offsetAddr; j<offsetAddr+numOf; j++){		
					if(
						MD_GET_BIT(
						MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[j>>4],j%16)
					){
							MD_SET_BIT(res[j>>3],j%8);
					}else{
							MD_CLR_BIT(res[j>>3],j%8);
					}
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL MDS_RTU_ReadRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *res, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	/*只能操作寄存器*/
	if(opAddrType != HOLD_REGS_TYPE && opAddrType != INPUT_REGS_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+numOf)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType == opAddrType){
				uint16 	j;
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				for(j=0;j<numOf;j++){
					res[j]=MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[offsetAddr+j];
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL MDS_RTU_WriteBit(void* obj,uint16 modbusAddr,uint8 bit, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	if(opAddrType != COILS_TYPE && opAddrType != INPUT_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+1)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType==opAddrType){
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				if(bit){
					MD_SET_BIT(
						MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[offsetAddr>>4],offsetAddr%16);
				}else{
					MD_CLR_BIT(
						MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[offsetAddr>>4],offsetAddr%16);
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL MDS_RTU_WriteBits(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *bit, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	if(opAddrType != COILS_TYPE && opAddrType != INPUT_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+numOf)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType==opAddrType){/*必须是BIT类型*/
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				uint16 j;
				for(j=0;j<numOf;j++){
					uint8 *byteData=(uint8*)bit;
					if(
						MD_GET_BIT( byteData[j>>3] ,j%8)
					){
						MD_SET_BIT(
							MDS_RTU_REG_COIL_ITEM_DATA(
							pModbusS_RTU->pRegCoilList[i])[(offsetAddr+j)>>4]
						,(j+offsetAddr)%16);
					}else{
						MD_CLR_BIT(
							MDS_RTU_REG_COIL_ITEM_DATA(
							pModbusS_RTU->pRegCoilList[i])[(offsetAddr+j)>>4]
						,(j+offsetAddr)%16);
					}
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL MDS_RTU_WriteReg(void* obj,uint16 modbusAddr,uint16 reg, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	if(opAddrType != HOLD_REGS_TYPE && opAddrType != INPUT_REGS_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+1)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType==opAddrType){
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[offsetAddr]=reg;
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL MDS_RTU_WriteRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *reg,uint8 isBigE, AddrType opAddrType){
	uint16 i;
	PModbusS_RTU pModbusS_RTU = obj;
	if(pModbusS_RTU==NULL){return FALSE;}
	if(opAddrType != HOLD_REGS_TYPE && opAddrType != INPUT_REGS_TYPE){return FALSE;}
	
	for(i=0;i<REG_COIL_ITEM_NUM;i++){
		if(pModbusS_RTU->pRegCoilList[i]==NULL){
			continue;
		}
		if(pModbusS_RTU->pRegCoilList[i]->modbusAddr<=modbusAddr&&
		(pModbusS_RTU->pRegCoilList[i]->modbusAddr+pModbusS_RTU->pRegCoilList[i]->modbusDataSize)>=(modbusAddr+numOf)
		){
			if(pModbusS_RTU->pRegCoilList[i]->addrType==opAddrType){/*必须是REG类型*/
				uint16 offsetAddr=modbusAddr-MDS_RTU_REG_COIL_ITEM_ADDR(pModbusS_RTU->pRegCoilList[i]);
				uint16 j=0;
				for(j=0;j<numOf;j++){
					MDS_RTU_REG_COIL_ITEM_DATA(pModbusS_RTU->pRegCoilList[i])[offsetAddr+j]=
					isBigE?MD_SWAP_HL(reg[j]):reg[j];
				}		
				return TRUE;
			}
		}
	}
	return FALSE;
}



BOOL MDS_RTU_WriteCoil(void* obj,uint16 modbusAddr,uint8 bit){
	return MDS_RTU_WriteBit( obj, modbusAddr, bit, COILS_TYPE);
}
BOOL MDS_RTU_WriteInput(void* obj,uint16 modbusAddr,uint8 bit){
	return MDS_RTU_WriteBit( obj, modbusAddr, bit, INPUT_TYPE);
}
BOOL MDS_RTU_WriteCoils(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *bit){
	return MDS_RTU_WriteBits( obj, modbusAddr, numOf,bit, COILS_TYPE);
}
BOOL MDS_RTU_WriteMulInput(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *bit){
	return MDS_RTU_WriteBits( obj, modbusAddr, numOf,bit, COILS_TYPE);
}
BOOL MDS_RTU_WriteHoldReg(void* obj,uint16 modbusAddr,uint16 reg){
	return MDS_RTU_WriteReg( obj, modbusAddr, reg, HOLD_REGS_TYPE);
}
BOOL MDS_RTU_WriteHoldRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *reg){
	return MDS_RTU_WriteRegs( obj, modbusAddr, numOf, reg,0, HOLD_REGS_TYPE);
}
BOOL MDS_RTU_WriteInputReg(void* obj,uint16 modbusAddr,uint16 reg){
	return MDS_RTU_WriteReg( obj, modbusAddr, reg, INPUT_REGS_TYPE);
}
BOOL MDS_RTU_WriteInputRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *reg){
	return MDS_RTU_WriteRegs( obj, modbusAddr, numOf, reg,0, INPUT_REGS_TYPE);
}
BOOL MDS_RTU_ReadCoils(void *obj,uint16 modbusAddr,uint16 numOf,uint8 *res){
	return MDS_RTU_ReadBits( obj, modbusAddr, numOf,res, COILS_TYPE);
}
BOOL MDS_RTU_ReadInput(void *obj,uint16 modbusAddr,uint16 numOf,uint8 *res){
	return MDS_RTU_ReadBits( obj, modbusAddr, numOf,res, INPUT_TYPE);
}
BOOL MDS_RTU_ReadHoldRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *res){
	return MDS_RTU_ReadRegs( obj, modbusAddr, numOf, res, HOLD_REGS_TYPE);
}
BOOL MDS_RTU_ReadInputRegs(void* obj,uint16 modbusAddr,uint16 numOf, uint16 *res){
	return MDS_RTU_ReadRegs( obj, modbusAddr, numOf, res, INPUT_REGS_TYPE);
}
