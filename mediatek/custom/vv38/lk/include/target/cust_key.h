#ifndef __CUST_KEY_H__
#define __CUST_KEY_H__

#include<cust_kpd.h>

/* BUG1605 - Modification for volume down key Start*/
//#define MT65XX_FACTORY_KEY	32
#define MT65XX_FACTORY_KEY_EVT	32
/* BUG1605 - Modification for volume down key End*/
#define MT65XX_META_KEY		42	/* KEY_2 */
#define MT65XX_PMIC_RST_KEY	32 /*for pmic key use*/
#define MT_CAMERA_KEY 		10

#define MT65XX_BOOT_MENU_KEY       0   /* KEY_VOLUMEUP */
#define MT65XX_MENU_SELECT_KEY     MT65XX_BOOT_MENU_KEY   
/* BUG1605 - Modification for volume down key Start*/
//#define MT65XX_MENU_OK_KEY         32 /* KEY_VOLUMEDOWN */
#define MT65XX_MENU_OK_KEY_EVT         32 /* KEY_VOLUMEDOWN For EVT*/
#define MT65XX_MENU_OK_KEY         1 /* KEY_VOLUMEDOWN For Later Phase*/
/* BUG1605 - Modification for volume down key End*/

#endif /* __CUST_KEY_H__ */
