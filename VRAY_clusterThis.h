/* ******************************************************************************
*
*  clusterThis mantra DSO for render time geo clustering
*
*    Digital Cinema Arts (C) 2008-2012
*
* This work is licensed under the Creative Commons Attribution-ShareAlike 2.5 License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/2.5/ or send a letter to
* Creative Commons, 543 Howard Street, 5th Floor, San Francisco, California, 94105, USA.
*
***************************************************************************** */

#ifndef __VRAY_clusterThis_h__
#define __VRAY_clusterThis_h__

//#define DEBUG

namespace
{

// This class is required by openvdb::tools::ParticlesToLeveSet
   class ParticleList
   {
      public:
         ParticleList(const GA_Detail * gdp,
                      openvdb::Real radiusMult = 1,
                      openvdb::Real velocityMult = 1) :
            mGdp(gdp),
            mVDBRadiusHandle(gdp, GEO_POINT_DICT, "vdb_radius"),
            mVelHandle(gdp, GEO_POINT_DICT, "v"),
            mHasRadius(mVDBRadiusHandle.isValid()),
            mHasVelocity(mVelHandle.isValid()),
            mRadiusMult(radiusMult),
            mVelocityMult(velocityMult) {
         }

         bool hasRadius()   const {
            return mHasRadius;
         }
         bool hasVelocity() const {
            return mHasVelocity;
         }

         // The public methods below are the only ones required
         // by tools::ParticlesToLevelSet
         size_t size() const {
            return mGdp->getNumPoints();
         }
         openvdb::Vec3R pos(int n) const {
            UT_Vector3 p = mGdp->getPos3(this->offset(n));
            return openvdb::Vec3R(p[0], p[1], p[2]);
         }
         openvdb::Vec3R vel(int n) const {
            if(!mHasVelocity)
               return openvdb::Vec3R(0, 0, 0);
            UT_Vector3 v = mVelHandle.get(this->offset(n));
            return mVelocityMult * openvdb::Vec3R(v[0], v[1], v[2]);
         }
         openvdb::Real radius(int n) const {
            if(!mHasRadius)
               return mRadiusMult;
            return mRadiusMult * mVDBRadiusHandle.get(this->offset(n));
         }

      protected:
         GA_Offset offset(int n) const {
            return mGdp->pointOffset(n);
         }

         const GA_Detail  *  mGdp;
         GA_ROHandleF        mVDBRadiusHandle;
         GA_ROHandleV3       mVelHandle;
         const bool          mHasRadius, mHasVelocity;
         const openvdb::Real mRadiusMult; // multiplier for radius
         const openvdb::Real mVelocityMult; // multiplier for velocity
   };// ParticleList

// Convenient settings struct
   struct Settings {
      Settings(): mRasterizeTrails(false), mFogVolume(false), mDx(1.0), mGradientWidth(-1.0) {}
      bool mRasterizeTrails, mFogVolume;
      float mDx, mGradientWidth;
   };

} // unnamed namespace


/* ******************************************************************************
*  Class Name : VRAY_clusterThis_Exception()
*
*  Description :  Exception class for VRAY_clusterThis mantra DSO
*
*
*  Input Arguments : None
*
*  Return Value : None
*
***************************************************************************** */
class VRAY_clusterThis_Exception
{
      std::string e_msg;
      int e_code;

   public:
      VRAY_clusterThis_Exception(std::string msg, int code);
//   ~VRAY_clusterThis_Exception();

      void what() {
         std::cout << "VRAY_clusterThis_Exception::what() - VRAY_clusterThis exception:  " << e_msg << endl;
      }

};


/* ******************************************************************************
*  Class Name : VRAY_clusterThis()
*
*  Description :  Class for VRAY_clusterThis mantra DSO
*
*
*  Input Arguments : None
*
*  Return Value : None
*
***************************************************************************** */
class VRAY_clusterThis : public VRAY_Procedural
{
   public:
      VRAY_clusterThis();
      virtual ~VRAY_clusterThis();

      virtual const char * getClassName();
      virtual int initialize(const UT_BoundingBox * box);
      virtual void getBoundingBox(UT_BoundingBox & box);
      virtual bool hasVolume() {
         return true;
      }
      virtual void render();

      static void exitClusterThis(void * data);
      void exitClusterThisReal(const char * fname);
      void exitClusterThisReal(void * data);


      struct exitData_struct {
         float exitTime;
         int exitCode;
      } exitData;


   private:

      friend class VRAY_clusterThisChild;

      struct pt_attr_offset_struct {

         // Required attributes
         GA_RWAttributeRef Cd;
         GA_RWAttributeRef Alpha;
         GA_RWAttributeRef v;
         GA_RWAttributeRef backtrack;
         GA_RWAttributeRef N;
         GA_RWAttributeRef up;
//         GA_RWAttributeRef orient;
         GA_RWAttributeRef material;
         GA_RWAttributeRef id;
         GA_RWAttributeRef pscale;
         GA_RWAttributeRef radius;
         GA_RWAttributeRef weight;
         GA_RWAttributeRef width;
         GA_RWAttributeRef vdb_radius;
         GA_RWAttributeRef geo_fname;

         // Optional attributes
         /*        GA_RWAttributeRef num_neighbors;
                 GA_RWAttributeRef force;
                 GA_RWAttributeRef vorticity;
                 GA_RWAttributeRef uv;
                 GA_RWAttributeRef age;
                 GA_RWAttributeRef viscosity;
                 GA_RWAttributeRef density;
                 GA_RWAttributeRef pressure;
                 GA_RWAttributeRef mass;
                 GA_RWAttributeRef temperature;*/

      } myPointAttrOffsets;


      struct file_attr_offset_struct {

         // Required attributes
         GA_RWAttributeRef Cd;
         GA_RWAttributeRef Alpha;
         GA_RWAttributeRef v;
         GA_RWAttributeRef N;
//      GA_RWAttributeRef orient;
         GA_RWAttributeRef material;
         GA_RWAttributeRef id;
         GA_RWAttributeRef inst_id;
//      GA_RWAttributeRef lod;
         GA_RWAttributeRef pscale;
//      GA_RWAttributeRef up;
//      GA_RWAttributeRef angle;
//      GA_RWAttributeRef offset;
//      GA_RWAttributeRef amp;

//      GA_RWAttributeRef low_bound;
//      GA_RWAttributeRef high_bound;
//      GA_RWAttributeRef deformspace;
//      GA_RWAttributeRef xformobj;

         GA_RWAttributeRef pointCd;
         GA_RWAttributeRef pointAlpha;
         GA_RWAttributeRef pointV;
         GA_RWAttributeRef pointBacktrack;
         GA_RWAttributeRef pointN;
         GA_RWAttributeRef pointMaterial;
         GA_RWAttributeRef pointPscale;
         GA_RWAttributeRef pointId;
         GA_RWAttributeRef pointInstId;
//      GA_RWAttributeRef pointLOD;
//      GA_RWAttributeRef pointUp;
//      GA_RWAttributeRef pointAngle;
//      GA_RWAttributeRef pointOffset;
//      GA_RWAttributeRef pointAmp;

      } myFileAttrOffsets;


      struct inst_attr_offset_struct {

         // Required attributes
         GA_RWAttributeRef Cd;
         GA_RWAttributeRef Alpha;
         GA_RWAttributeRef v;
         GA_RWAttributeRef N;
//         GA_RWAttributeRef orient;
         GA_RWAttributeRef material;
         GA_RWAttributeRef id;
         GA_RWAttributeRef inst_id;
         GA_RWAttributeRef pscale;
         GA_RWAttributeRef radius;
         GA_RWAttributeRef weight;
         GA_RWAttributeRef width;

         GA_RWAttributeRef pointCd;
         GA_RWAttributeRef pointAlpha;
         GA_RWAttributeRef pointV;
         GA_RWAttributeRef pointBacktrack;
         GA_RWAttributeRef pointN;
         GA_RWAttributeRef pointUp;
//         GA_RWAttributeRef pointOrient;
         GA_RWAttributeRef pointMaterial;
         GA_RWAttributeRef pointId;
         GA_RWAttributeRef pointWeight;
         GA_RWAttributeRef pointWidth;
         GA_RWAttributeRef pointInstId;
         GA_RWAttributeRef pointPscale;
         GA_RWAttributeRef pointRadius;
         GA_RWAttributeRef pointVDBRadius;

         // Optional attributes
         //GA_RWAttributeRef num_neighbors;
         //GA_RWAttributeRef force;
         //GA_RWAttributeRef vorticity;
         //GA_RWAttributeRef uv;
         //GA_RWAttributeRef age;
         //GA_RWAttributeRef viscosity;
         //GA_RWAttributeRef density;
         //GA_RWAttributeRef pressure;
         //GA_RWAttributeRef mass;
         //GA_RWAttributeRef temperature;

      } myInstAttrRefs;



      struct inst_mb_attr_offset_struct {

         // Required attributes
         GA_RWAttributeRef Cd;
         GA_RWAttributeRef Alpha;
         GA_RWAttributeRef v;
         GA_RWAttributeRef N;
//         GA_RWAttributeRef orient;
         GA_RWAttributeRef material;
         GA_RWAttributeRef id;
         GA_RWAttributeRef inst_id;
         GA_RWAttributeRef pscale;
         GA_RWAttributeRef radius;
         GA_RWAttributeRef weight;
         GA_RWAttributeRef width;

         GA_RWAttributeRef pointCd;
         GA_RWAttributeRef pointAlpha;
         GA_RWAttributeRef pointV;
         GA_RWAttributeRef pointBacktrack;
         GA_RWAttributeRef pointN;
         GA_RWAttributeRef pointUp;
//         GA_RWAttributeRef pointOrient;
         GA_RWAttributeRef pointMaterial;
         GA_RWAttributeRef pointWeight;
         GA_RWAttributeRef pointWidth;
         GA_RWAttributeRef pointId;
         GA_RWAttributeRef pointInstId;
         GA_RWAttributeRef pointPscale;
         GA_RWAttributeRef pointRadius;
         GA_RWAttributeRef pointVDBRadius;

         // Optional attributes
         //GA_RWAttributeRef num_neighbors;
         //GA_RWAttributeRef force;
         //GA_RWAttributeRef vorticity;
         //GA_RWAttributeRef uv;
         //GA_RWAttributeRef age;
         //GA_RWAttributeRef viscosity;
         //GA_RWAttributeRef density;
         //GA_RWAttributeRef pressure;
         //GA_RWAttributeRef mass;
         //GA_RWAttributeRef temperature;

      } myInstMBAttrOffsets;


      struct pt_attr_struct {
         // Required attributes
         UT_Vector4 myPos;
         UT_Vector4 myNewPos;
         UT_Vector4 myMBPos;

         UT_Vector3 Cd;
         fpreal Alpha;
         UT_Vector3 v;
         UT_Vector4 backtrack;
         UT_Vector3 N;
         UT_Vector3 up;
//         UT_Vector4 orient;
         uint32 id;
         fpreal radius;
         fpreal vdb_radius;
         fpreal pscale;
         fpreal weight;
         fpreal width;
         UT_String material;
         UT_String geo_fname;

//         fpreal theta;

         // Optional attributes
         /*        uint32 num_neighbors;
                 UT_Vector3 force;
                 UT_Vector3 vorticity;
                 UT_Vector3 uv;
                 fpreal age;
                 fpreal viscosity;
                 fpreal density;
                 fpreal pressure;
                 fpreal mass;
                 fpreal temperature;*/
      } myPointAttributes;


      void calculateNewPosition(fpreal theta, uint32 i, uint32 j);
      void dumpParameters();
      int preLoadGeoFile(GU_Detail * file_gdp);
      void createAttributeOffsets(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int getAttributeOffsets(GU_Detail * gdp);
      int getAttributes(GEO_Point * ppt, GU_Detail * gdp);
      void checkRequiredAttributes();
      int addFileAttributeOffsets(GU_Detail * gdp);
      void setInstanceAttributes(GEO_Primitive * myGeoPrim);
      void setPointInstanceAttributes(GU_Detail * gdp, GEO_Point * ppt);
      int setFileAttributes(GU_Detail * gdp);
      int getOTLParameters();
      int runCVEX(GU_Detail * inst_gdp, GU_Detail * mb_gdp, UT_String theCVEXFname, uint method);

      // voxel processing
      int convertVDBUnits();
      void convert(openvdb::ScalarGrid::Ptr, ParticleList&, const Settings&, hvdb::Interrupter &);
      void preProcess(GU_Detail * gdp);
      void postProcess(GU_Detail * gdp, GU_Detail * inst_gdp, GU_Detail * mb_gdp);


      // Instancing methods
      int instancePoint(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceSphere(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceCube(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceGrid(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceTube(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceCircle(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceCurve(GU_Detail * inst_gdp, GU_Detail * mb_gdp, fpreal theta, long int point_num);
      int instanceMetaball(GU_Detail * inst_gdp, GU_Detail * mb_gdp);
      int instanceFile(GU_Detail * file_gdp, GU_Detail * inst_gdp, GU_Detail * mb_gdp);

      // member variables
      GU_Detail * myGdp;
      UT_BoundingBox myBox;
      UT_BoundingBox myVelBox;
      fpreal bb_x1, bb_x2, bb_y1, bb_y2, bb_z1, bb_z2;
      UT_String myMaterial;
      UT_Matrix3 myXformInverse;
      bool tempFileDeleted;
      UT_Noise myNoise;
      UT_MersenneTwister myMersenneTwister;
      bool myUsePointRadius;
//      bool myUsePointGeoFname;
      bool myUseBacktrackMB;
      UT_IntArray myPointList;
      UT_String myObjectName;
      UT_String myOTLVersion;
      fpreal   myVelocityScale;
      long int myInstanceNum;
      fpreal   myLOD;
      static const fpreal myFPS = 24.0;

      GU_Detail * myFileGDP;
      openvdb::ScalarGrid::Ptr myGeoGrid;
      openvdb::VectorGrid::Ptr myGradientGrid;


      // Parameters
      uint32   myNumCopies;
      bool     myUseGeoFile;
      UT_String mySrcGeoFname;
      uint32   myPrimType;
      uint32   myMethod;
      fpreal   mySize[3];
      uint32   myRecursion;
      fpreal   myFreqX, myFreqY, myFreqZ;
      fpreal   myOffsetX, myOffsetY, myOffsetZ;
      fpreal   myRadius;
      fpreal   myBirthProb;
      uint32   myDoMotionBlur;
      fpreal   myShutter;
      fpreal   myShutter2;
      int      myNoiseType;
      fpreal   myRough;
      fpreal   myCurrentTime;
      fpreal   myNoiseAmp;
      fpreal   myNoiseAtten;
      UT_Vector3 myNoiseVec;
      int      myNoiseSeed;
      int      myFractalDepth;
      bool     myCopyAttrs;
      bool     myBlendAttrs;
      uint32   myFilterType;
      fpreal   myFilterAmp;
      UT_String myGeoFile;
      UT_String myTempFname;
      bool      myUseTempFile;
      bool      mySaveTempFile;
      UT_String myCVEXFname;
      bool     myCVEX_Exec;
      UT_String myCVEXFname_prim;
      bool     myCVEX_Exec_prim;
      UT_String myCVEXFname_pre;
      bool     myCVEX_Exec_pre;
      UT_String myCVEXFname_post;
      bool     myCVEX_Exec_post;
      int      myVerbose;

      // VDB pre processing parms
      int      myPreProcess;
      int      myPreRasterType;
      fpreal   myPreDx;
      int      myPreFogVolume;
      fpreal   myPreGradientWidth;
      fpreal   myPreVoxelSize;
      fpreal   myPreRadiusMin;
      fpreal   myPreBandWidth;
      int      myPreWSUnits;
      fpreal   myPreVDBVelocityMult;
      fpreal   myPreVDBRadiusMult;
      fpreal   myPreFalloff;
      fpreal   myPrePosInfluence;
      fpreal   myPreNormalInfluence;
      fpreal   myPreVelInfluence;

      int      myPreVDBMedianFilter;
      int      myPreVDBMeanFilter;
      int      myPreVDBMeanCurvatureFilter;
      int      myPreVDBLaplacianFilter;
      int      myPreVDBOffsetFilter;
      fpreal   myPreVDBOffsetFilterAmount;
      int      myPreVDBReNormalizeFilter;
      int      myPreVDBWriteDebugFiles;

      // VDB post processing parms
      int      myPostProcess;
      int      myRasterType;
      fpreal   myDx;
      int      myFogVolume;
      fpreal   myGradientWidth;
      fpreal   myVoxelSize;
      fpreal   myRadiusMin;
      fpreal   myBandWidth;
      int      myWSUnits;
      fpreal   myVDBVelocityMult;
      fpreal   myVDBRadiusMult;
      fpreal   myFalloff;
      fpreal   myPosInfluence;
      fpreal   myNormalInfluence;
      fpreal   myVelInfluence;

      int      myVDBMedianFilter;
      int      myVDBMeanFilter;
      int      myVDBMeanCurvatureFilter;
      int      myVDBLaplacianFilter;
      int      myVDBOffsetFilter;
      fpreal   myVDBOffsetFilterAmount;
      int      myVDBReNormalizeFilter;
      int      myVDBWriteDebugFiles;

      // A struct to keep track os CVEX vars to pass to the CVEX code
      struct cvex_pt_vars_struct {
      uint  cvex_Cd_pt:
         1;
      uint  cvex_Alpha_pt:
         1;
      uint  cvex_v_pt:
         1;
      uint  cvex_N_pt:
         1;
      uint  cvex_pscale_pt:
         1;
      } myCVEXPointVars;

      struct cvex_prim_vars_struct {
      uint  cvex_Cd_prim:
         1;
      uint  cvex_Alpha_prim:
         1;
      uint  cvex_v_prim:
         1;
      uint  cvex_N_prim:
         1;
      uint  cvex_pscale_prim:
         1;
      uint  cvex_weight_prim:
         1;
      uint  cvex_width_prim:
         1;
      } myCVEXPrimVars;


      enum clusterPrimTypeEnum {
         CLUSTER_POINT = 0,
         CLUSTER_PRIM_SPHERE,
         CLUSTER_PRIM_CUBE,
         CLUSTER_PRIM_GRID,
         CLUSTER_PRIM_TUBE,
         CLUSTER_PRIM_CIRCLE,
         CLUSTER_PRIM_CURVE,
         CLUSTER_PRIM_METABALL,
         CLUSTER_FILE
      };

      enum clusterMotionBlurTypeEnum {
         CLUSTER_MB_NONE = 0,
         CLUSTER_MB_VELOCITY,
         CLUSTER_MB_DEFORMATION
      };

      enum clusterVerboseTypeEnum {
         CLUSTER_MSG_QUIET = 0,
         CLUSTER_MSG_INFO,
         CLUSTER_MSG_VERBOSE,
         CLUSTER_MSG_DEBUG
      };

      enum clusterInstanceMethod {
         CLUSTER_INSTANCE_NOW = 0,
         CLUSTER_INSTANCE_DEFERRED
      };

      enum clusterCVEXMethod {
         CLUSTER_CVEX_POINT = 0,
         CLUSTER_CVEX_PRIM
      };

};



#endif




