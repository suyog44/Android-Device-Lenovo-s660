#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov8825raw.h"
#include "camera_info_ov8825raw.h"
#include "camera_custom_AEPlinetable.h"
#include "camera_custom_tsf_tbl.h"
const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,
    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    	}
    },
    ISPPca:{
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
        },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
        }
    }},
    ISPCcmPoly22:{
        75170,    // i4R_AVG
        13190,    // i4R_STD
        79140,    // i4B_AVG
        26270,    // i4B_STD
        {  // i4P00[9]
            4448648, -1494813, -393843, -604477, 3414513, -250036, 85095, -1385454, 3860283
        },
        {  // i4P10[9]
            933698, -628943, -304758, -247520, -22220, 269740, -73861, 196166, -122555
        },
        {  // i4P01[9]
            814367, -494023, -320352, -358410, -180556, 538966, -57406, -190454, 247689
        },
        {  // i4P20[9]
            394007, -491950, 98031, -21525, 59812, -38287, 140879, -521951, 381045
        },
        {  // i4P11[9]
            -35750, -344806, 380738, 121574, 59500, -181074, 143388, -309535, 166309
        },
        {  // i4P02[9]
            -315751, 65233, 250618, 151463, 0, 0, 0, 0, 0
        }
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1144,    // u4MinGain, 1024 base = 1x
            10240,    // u4MaxGain, 16x
            100,    // u4MiniISOGain, ISOxx  
            128,    // u4GainStepUnit, 1x/8 
            26355,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            17763,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            512,    // u4Video2PreRatio, 1024 base = 1x 
            17763,    // u4CapExpUnit 
            23,    // u4CapMaxFrameRate
            512,    // u4Cap2PreRatio, 1024 base = 1x
            24,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            2,    // u4HistHighThres
            40,    // u4HistLowThres
            2,    // u4MostBrightRatio
            1,    // u4MostDarkRatio
            160,    // u4CentralHighBound
            20,    // u4CentralLowBound
            {240, 230, 220, 210, 200},    // u4OverExpThres[AE_CCT_STRENGTH_NUM] 
            {75, 108, 128, 148, 170},    // u4HistStretchThres[AE_CCT_STRENGTH_NUM] 
            {18, 22, 26, 30, 34}    // u4BlackLightThres[AE_CCT_STRENGTH_NUM] 
        },
        // rCCTConfig
        {
            TRUE,    // bEnableBlackLight
            TRUE,    // bEnableHistStretch
            FALSE,    // bEnableAntiOverExposure
            TRUE,    // bEnableTimeLPF
            FALSE,    // bEnableCaptureThres
            FALSE,    // bEnableVideoThres
            FALSE,    // bEnableStrobeThres
            47,    // u4AETarget
            0,    // u4StrobeAETarget
            50,    // u4InitIndex
            4,    // u4BackLightWeight
            32,    // u4HistStretchWeight
            4,    // u4AntiOverExpWeight
            2,    // u4BlackLightStrengthIndex
            2,    // u4HistStretchStrengthIndex
            2,    // u4AntiOverExpStrengthIndex
            2,    // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8},    // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM] 
            90,    // u4InDoorEV = 9.0, 10 base 
            -5,    // i4BVOffset delta BV = value/10 
            64,    // u4PreviewFlareOffset
            64,    // u4CaptureFlareOffset
            3,    // u4CaptureFlareThres
            64,    // u4VideoFlareOffset
            3,    // u4VideoFlareThres
            64,    // u4StrobeFlareOffset
            3,    // u4StrobeFlareThres
            160,    // u4PrvMaxFlareThres
            0,    // u4PrvMinFlareThres
            160,    // u4VideoMaxFlareThres
            0,    // u4VideoMinFlareThres
            18,    // u4FlatnessThres    // 10 base for flatness condition.
            55    // u4FlatnessStrength
        }
    },
    // AWB NVRAM
    {
        // AWB calibration data
        {
            // rUnitGain (unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rGoldenGain (golden sample gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                823,    // i4R
                512,    // i4G
                649    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                88,    // i4X
                -263    // i4Y
            },
            // Horizon
            {
                -435,    // i4X
                -317    // i4Y
            },
            // A
            {
                -331,    // i4X
                -324    // i4Y
            },
            // TL84
            {
                -182,    // i4X
                -380    // i4Y
            },
            // CWF
            {
                -130,    // i4X
                -463    // i4Y
            },
            // DNP
            {
                -1,    // i4X
                -295    // i4Y
            },
            // D65
            {
                88,    // i4X
                -263    // i4Y
            },
            // DF
            {
                46,    // i4X
                -367    // i4Y
            }
        },
        // Rotated XY coordinate of AWB light source
        {
            // Strobe
            {
                46,    // i4X
                -274    // i4Y
            },
            // Horizon
            {
                -479,    // i4X
                -245    // i4Y
            },
            // A
            {
                -378,    // i4X
                -268    // i4Y
            },
            // TL84
            {
                -239,    // i4X
                -347    // i4Y
            },
            // CWF
            {
                -201,    // i4X
                -437    // i4Y
            },
            // DNP
            {
                -47,    // i4X
                -291    // i4Y
            },
            // D65
            {
                46,    // i4X
                -274    // i4Y
            },
            // DF
            {
                -12,    // i4X
                -370    // i4Y
            }
        },
        // AWB gain of AWB light source
        {
            // Strobe 
            {
                823,    // i4R
                512,    // i4G
                649    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                601,    // i4G
                1664    // i4B
            },
            // A 
            {
                512,    // i4R
                517,    // i4G
                1253    // i4B
            },
            // TL84 
            {
                669,    // i4R
                512,    // i4G
                1096    // i4B
            },
            // CWF 
            {
                803,    // i4R
                512,    // i4G
                1143    // i4B
            },
            // DNP 
            {
                763,    // i4R
                512,    // i4G
                764    // i4B
            },
            // D65 
            {
                823,    // i4R
                512,    // i4G
                649    // i4B
            },
            // DF 
            {
                895,    // i4R
                512,    // i4G
                790    // i4B
            }
        },
        // Rotation matrix parameter
        {
            9,    // i4RotationAngle
            253,    // i4Cos
            40    // i4Sin
        },
        // Daylight locus parameter
        {
            -173,    // i4SlopeNumerator
            128    // i4SlopeDenominator
        },
        // AWB light area
        {
            // Strobe:FIXME
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            },
            // Tungsten
            {
            -289,    // i4RightBound
            -939,    // i4LeftBound
            -206,    // i4UpperBound
            -306    // i4LowerBound
            },
            // Warm fluorescent
            {
            -289,    // i4RightBound
            -939,    // i4LeftBound
            -306,    // i4UpperBound
            -426    // i4LowerBound
            },
            // Fluorescent
            {
            -97,    // i4RightBound
            -289,    // i4LeftBound
            -200,    // i4UpperBound
            -392    // i4LowerBound
            },
            // CWF
            {
            -97,    // i4RightBound
            -289,    // i4LeftBound
            -392,    // i4UpperBound
            -487    // i4LowerBound
            },
            // Daylight
            {
            71,    // i4RightBound
            -97,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Shade
            {
            431,    // i4RightBound
            71,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            121,    // i4RightBound
            -97,    // i4LeftBound
            -354,    // i4UpperBound
            -469    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            431,    // i4RightBound
            -939,    // i4LeftBound
            0,    // i4UpperBound
            -487    // i4LowerBound
            },
            // Daylight
            {
            96,    // i4RightBound
            -97,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Cloudy daylight
            {
            196,    // i4RightBound
            21,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Shade
            {
            296,    // i4RightBound
            21,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Twilight
            {
            -97,    // i4RightBound
            -257,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Fluorescent
            {
            96,    // i4RightBound
            -339,    // i4LeftBound
            -224,    // i4UpperBound
            -487    // i4LowerBound
            },
            // Warm fluorescent
            {
            -278,    // i4RightBound
            -478,    // i4LeftBound
            -224,    // i4UpperBound
            -487    // i4LowerBound
            },
            // Incandescent
            {
            -278,    // i4RightBound
            -478,    // i4LeftBound
            -194,    // i4UpperBound
            -354    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
            }
        },
        // PWB default gain	
        {
            // Daylight
            {
            782,    // i4R
            512,    // i4G
            697    // i4B
            },
            // Cloudy daylight
            {
            884,    // i4R
            512,    // i4G
            589    // i4B
            },
            // Shade
            {
            935,    // i4R
            512,    // i4G
            545    // i4B
            },
            // Twilight
            {
            641,    // i4R
            512,    // i4G
            917    // i4B
            },
            // Fluorescent
            {
            774,    // i4R
            512,    // i4G
            922    // i4B
            },
            // Warm fluorescent
            {
            580,    // i4R
            512,    // i4G
            1371    // i4B
            },
            // Incandescent
            {
            511,    // i4R
            512,    // i4G
            1251    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            0,    // i4SliderValue
            6672    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            5624    // i4OffsetThr
            },
            // Shade
            {
            0,    // i4SliderValue
            1345    // i4OffsetThr
            },
            // Daylight WB gain
            {
            742,    // i4R
            512,    // i4G
            749    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: CWF
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: shade
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        {// CCT estimation
            {// CCT
                2300,    // i4CCT[0]
                2850,    // i4CCT[1]
                4100,    // i4CCT[2]
                5100,    // i4CCT[3]
                6500    // i4CCT[4]
            },
            {// Rotated X coordinate
                -525,    // i4RotatedXCoordinate[0]
                -424,    // i4RotatedXCoordinate[1]
                -285,    // i4RotatedXCoordinate[2]
                -93,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
            }
        }
    },
    {0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace

const CAMERA_TSF_TBL_STRUCT CAMERA_TSF_DEFAULT_VALUE =
{
    #include INCLUDE_FILENAME_TSF_PARA
    #include INCLUDE_FILENAME_TSF_DATA
};


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T),
                                             0,
                                             sizeof(CAMERA_TSF_TBL_STRUCT)};

    if (CameraDataType > CAMERA_DATA_TSF_TABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
        case CAMERA_DATA_TSF_TABLE:
            memcpy(pDataBuf,&CAMERA_TSF_DEFAULT_VALUE,sizeof(CAMERA_TSF_TBL_STRUCT));
            break;
        default:
            break;
    }
    return 0;
}}; // NSFeature


