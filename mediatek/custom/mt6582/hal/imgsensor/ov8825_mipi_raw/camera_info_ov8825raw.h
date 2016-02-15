#ifndef _CAMERA_INFO_OV8825RAW_H
#define _CAMERA_INFO_OV8825RAW_H

/*******************************************************************************
*   Configuration
********************************************************************************/
#define SENSOR_ID                           OV8825_SENSOR_ID
#define SENSOR_DRVNAME                      SENSOR_DRVNAME_OV8825_MIPI_RAW
#define INCLUDE_FILENAME_ISP_REGS_PARAM     "camera_isp_regs_ov8825raw.h"
#define INCLUDE_FILENAME_ISP_PCA_PARAM      "camera_isp_pca_ov8825raw.h"
#define INCLUDE_FILENAME_ISP_LSC_PARAM      "camera_isp_lsc_ov8825raw.h"

/* [VV38] S John_Wang BUG#xxx Enable TSF */
#define INCLUDE_FILENAME_TSF_PARA           "camera_tsf_para_ov8825raw.h"
#define INCLUDE_FILENAME_TSF_DATA           "camera_tsf_data_ov8825raw.h"
/* [VV38] E John_Wang BUG#xxx Enable TSF */
/*******************************************************************************
*
********************************************************************************/


#endif
