/* ******************************************************************************
*
*  VRAY_clusterThisAttributeUtils
*
*
* Description :
*
*
***************************************************************************** */

#ifndef __VRAY_clusterThisAttributeUtils_cpp__
#define __VRAY_clusterThisAttributeUtils_cpp__


/* ******************************************************************************
*  Function Name : createAttributeRefs()
*
*  Description :   Create the attribute the references for the instanced objects
*
*  Input Arguments : GU_Detail *inst_gdp
*
*  Return Value : void
*
***************************************************************************** */
void VRAY_clusterThis::createAttributeRefs(GU_Detail * inst_gdp, GU_Detail * mb_gdp,
                                           VRAY_clusterThis::inst_attr_ref_struct * theInstAttrRefs)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::createAttributeRefs() " << endl;
#endif

// TODO: Check all these references with *.isValid() and throw exeception if it fails !!!

   if(myPrimType != CLUSTER_POINT) {

#ifdef DCA_DEBUG
         cout << "VRAY_clusterThis::createAttributeRefs() Creating primitive attributes" << endl;
#endif

         theInstAttrRefs->Cd = inst_gdp->addDiffuseAttribute(GEO_PRIMITIVE_DICT);
         theInstAttrRefs->Alpha = inst_gdp->addAlphaAttribute(GEO_PRIMITIVE_DICT);
         theInstAttrRefs->v = inst_gdp->addVelocityAttribute(GEO_PRIMITIVE_DICT);
         theInstAttrRefs->N = inst_gdp->addNormalAttribute(GEO_PRIMITIVE_DICT);
         theInstAttrRefs->radius = inst_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "radius", 1);
         theInstAttrRefs->pscale = inst_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "pscale", 1);
         theInstAttrRefs->weight = inst_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "weight", 1);
         theInstAttrRefs->width = inst_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "width", 1);
         theInstAttrRefs->id = inst_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "id", 1);
         theInstAttrRefs->inst_id = inst_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "inst_id", 1);
         theInstAttrRefs->material = inst_gdp->addStringTuple(GA_ATTRIB_PRIMITIVE, "shop_materialpath", 1);

         theInstAttrRefs->pointCd = inst_gdp->addDiffuseAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointAlpha = inst_gdp->addAlphaAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointV = inst_gdp->addVelocityAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointN = inst_gdp->addNormalAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointRadius = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "radius", 1);
         theInstAttrRefs->pointPscale = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
         theInstAttrRefs->pointWeight = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "weight", 1);
         theInstAttrRefs->pointWidth = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "width", 1);
         theInstAttrRefs->pointId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
         theInstAttrRefs->pointInstId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "inst_id", 1);
         theInstAttrRefs->pointMaterial = inst_gdp->addStringTuple(GA_ATTRIB_POINT, "shop_materialpath", 1);

         if(myDoMotionBlur == CLUSTER_MB_DEFORMATION) {
               myInstMBAttrRefs.Cd = mb_gdp->addDiffuseAttribute(GEO_PRIMITIVE_DICT);
               myInstMBAttrRefs.Alpha = mb_gdp->addAlphaAttribute(GEO_PRIMITIVE_DICT);
               myInstMBAttrRefs.v = mb_gdp->addVelocityAttribute(GEO_PRIMITIVE_DICT);
               myInstMBAttrRefs.N = mb_gdp->addNormalAttribute(GEO_PRIMITIVE_DICT);
               myInstMBAttrRefs.radius = mb_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "radius", 1);
               myInstMBAttrRefs.pscale = mb_gdp->addFloatTuple(GA_ATTRIB_PRIMITIVE, "pscale", 1);
               myInstMBAttrRefs.id = mb_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "id", 1);
               myInstMBAttrRefs.inst_id = mb_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "inst_id", 1);
               myInstMBAttrRefs.material = mb_gdp->addStringTuple(GA_ATTRIB_PRIMITIVE, "shop_materialpath", 1);

               myInstMBAttrRefs.pointCd = mb_gdp->addDiffuseAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointAlpha = mb_gdp->addAlphaAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointV = mb_gdp->addVelocityAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointN = mb_gdp->addNormalAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointRadius = mb_gdp->addFloatTuple(GA_ATTRIB_POINT, "radius", 1);
               myInstMBAttrRefs.pointPscale = mb_gdp->addFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
               myInstMBAttrRefs.pointId = mb_gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
               myInstMBAttrRefs.pointInstId = mb_gdp->addIntTuple(GA_ATTRIB_POINT, "inst_id", 1);
               myInstMBAttrRefs.pointMaterial = mb_gdp->addStringTuple(GA_ATTRIB_POINT, "shop_materialpath", 1);
            }
      }


   // Do the point attribute creation

   if(myPrimType == CLUSTER_POINT) {
#ifdef DCA_DEBUG
         cout << "VRAY_clusterThis::createAttributeRefs() Creating Point attributes" << endl;
#endif

         theInstAttrRefs->pointCd = inst_gdp->addDiffuseAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointAlpha = inst_gdp->addAlphaAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointV = inst_gdp->addVelocityAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointN = inst_gdp->addNormalAttribute(GEO_POINT_DICT);
         theInstAttrRefs->pointRadius = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "radius", 1);
         theInstAttrRefs->pointPscale = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
         theInstAttrRefs->pointId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
         theInstAttrRefs->pointInstId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "inst_id", 1);
         theInstAttrRefs->pointMaterial = inst_gdp->addStringTuple(GA_ATTRIB_POINT, "shop_materialpath", 1);

         if(myDoMotionBlur == CLUSTER_MB_DEFORMATION) {
               myInstMBAttrRefs.pointCd = mb_gdp->addDiffuseAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointAlpha = mb_gdp->addAlphaAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointV = mb_gdp->addVelocityAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointN = mb_gdp->addNormalAttribute(GEO_POINT_DICT);
               myInstMBAttrRefs.pointRadius = mb_gdp->addFloatTuple(GA_ATTRIB_POINT, "radius", 1);
               myInstMBAttrRefs.pointPscale = mb_gdp->addFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
               myInstMBAttrRefs.pointId = mb_gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
               myInstMBAttrRefs.pointInstId = mb_gdp->addIntTuple(GA_ATTRIB_POINT, "inst_id", 1);
               myInstMBAttrRefs.pointMaterial = mb_gdp->addStringTuple(GA_ATTRIB_POINT, "shop_materialpath", 1);
            }
      }
}



/* ******************************************************************************
*  Function Name : getAttributeRefs()
*
*  Description :   Get the attribute the references of the incoming geometry
*
*  Input Arguments : GU_Detail *inst_gdp
*
*  Return Value : int status
*
***************************************************************************** */
int VRAY_clusterThis::getAttributeRefs(GU_Detail * inst_gdp)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::getAttributeRefs() " << endl;
#endif


   try {

         myPointAttrRefs.Cd = inst_gdp->findDiffuseAttribute(GEO_POINT_DICT);
         myPointAttrRefs.Alpha = inst_gdp->findAlphaAttribute(GEO_POINT_DICT);

         myPointAttrRefs.v = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "v", 3);
         myPointAttrRefs.backtrack = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "backtrack", 4);
         myPointAttrRefs.N = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "N", 3);
         myPointAttrRefs.up = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "up", 3);
//         myPointAttrRefs.orient = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "orient", 4);

         myPointAttrRefs.radius = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "radius", 1);
         if(myPointAttrRefs.radius.isValid())
            myUsePointRadius = 1;

         myPointAttrRefs.vdb_radius = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "vdb_radius", 1);
         myPointAttrRefs.pscale = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
         myPointAttrRefs.width = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "width", 1);
         myPointAttrRefs.id = inst_gdp->findIntTuple(GA_ATTRIB_POINT, "id", 1);
         myPointAttrRefs.material = inst_gdp->findStringTuple(GA_ATTRIB_POINT, "shop_materialpath");

         if(myPrimType == CLUSTER_PRIM_METABALL)
            myPointAttrRefs.weight = inst_gdp->findFloatTuple(GA_ATTRIB_POINT, "weight", 1);

         if(myPrimType == CLUSTER_FILE)
            myPointAttrRefs.geo_fname = inst_gdp->findStringTuple(GA_ATTRIB_POINT, "geo_fname");


         /*    myPointAttrRefs.uv = inst_gdp->findTextureAttribute ( GEO_POINT_DICT );
             myPointAttrRefs.force = inst_gdp->pointAttribs().getOffset ( "force", GB_ATTRIB_VECTOR );
             myPointAttrRefs.vorticity = inst_gdp->pointAttribs().getOffset ( "vorticity", GB_ATTRIB_VECTOR );
             myPointAttrRefs.age = inst_gdp->pointAttribs().getOffset ( "age", GB_ATTRIB_FLOAT );
             myPointAttrRefs.viscosity = inst_gdp->pointAttribs().getOffset ( "viscosity", GB_ATTRIB_FLOAT );
             myPointAttrRefs.pressure = inst_gdp->pointAttribs().getOffset ( "pressure", GB_ATTRIB_FLOAT );
             myPointAttrRefs.density = inst_gdp->pointAttribs().getOffset ( "density", GB_ATTRIB_FLOAT );
             myPointAttrRefs.mass = inst_gdp->pointAttribs().getOffset ( "mass", GB_ATTRIB_FLOAT );
             myPointAttrRefs.temperature = inst_gdp->pointAttribs().getOffset ( "temperature", GB_ATTRIB_FLOAT );
             myPointAttrRefs.num_neighbors = inst_gdp->pointAttribs().getOffset ( "num_neighbors", GB_ATTRIB_INT );*/

      }
   // Process exceptions ...
   catch(VRAY_clusterThis_Exception e) {
         e.what();
         cout << "VRAY_clusterThis::getAttributeRefs() - Exception encountered, exiting" << endl << endl;
         return 1;
      }


#ifdef DCA_DEBUG
   cout << "Geometry attribute references:" << endl;
   cout << "Cd: " << myPointAttrRefs.Cd.isValid() << endl;
   cout << "Alpha: " << myPointAttrRefs.Alpha.isValid() << endl;
   cout << "v: " << myPointAttrRefs.v.isValid() << endl;
   cout << "backtrack: " << myPointAttrRefs.backtrack.isValid() << endl;
   cout << "up: " << myPointAttrRefs.up.isValid() << endl;
   cout << "N: " << myPointAttrRefs.N.isValid() << endl;
//   cout << "orient: " << myPointAttrRefs.orient.isValid() << endl;
   cout << "pscale: " << myPointAttrRefs.pscale.isValid() << endl;
   cout << "id: " << myPointAttrRefs.id.isValid() << endl;
   cout << "weight: " << myPointAttrRefs.weight.isValid() << endl;
   cout << "material: " << myPointAttrRefs.material.isValid() << endl;
   cout << "geo_fname: " << myPointAttrRefs.geo_fname.isValid() << endl;

//     cout << "uv: " << myPointAttrRefs.uv.isValid() << endl;
//     cout << "age: " << myPointAttrRefs.age.isValid() << endl;
//     cout << "force: " << myPointAttrRefs.force.isValid() << endl;
//     cout << "viscosity: " << myPointAttrRefs.viscosity.isValid() << endl;
//     cout << "vorticity: " << myPointAttrRefs.vorticity.isValid() << endl;
//     cout << "pressure: " << myPointAttrRefs.pressure.isValid() << endl;
//     cout << "density: " << myPointAttrRefs.density.isValid() << endl;
//     cout << "mass: " << myPointAttrRefs.mass.isValid() << endl;
//     cout << "temperature: " << myPointAttrRefs.temperature.isValid() << endl;
//     cout << "num_neighbors: " << myPointAttrRefs.num_neighbors.isValid() << endl;
#endif

//    cout << "VRAY_clusterThis::getAttributeRefs() exiting" << endl;

   return 0;
}



/* ******************************************************************************
*  Function Name : checkRequiredAttributes
*
*  Description :  Check that all the required attributes are in the point cloud
*
*  Input Arguments : None
*
*  Return Value : None
*
***************************************************************************** */
void VRAY_clusterThis::checkRequiredAttributes()
{

   // TODO: Confirm that all required attrs are being checked for each instance type

//   std::cout << "VRAY_clusterThis::checkRequiredAttributes()" << std::endl;
   // Check for required attributes
   if(myPointAttrRefs.Cd.isInvalid()) {
         cout << "Incoming points must have Cd attribute! Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have Cd attribute! ", 1);
      }

   if(myPointAttrRefs.Alpha.isInvalid()) {
         cout << "Incoming points must have Alpha attribute! Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have Alpha attribute! ", 1);
      }

   if(myPointAttrRefs.v.isInvalid()) {
         cout << "Incoming points must have v attribute! Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have v attribute! ", 1);
      }

   if(myPointAttrRefs.N.isInvalid()) {
         cout << "Incoming points must have N attribute! Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have N attribute! ", 1);
      }

   if(myPointAttrRefs.pscale.isInvalid()) {
         cout << "Incoming points must have pscale attribute! Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have pscale attribute! ", 1);
      }

   if(myPointAttrRefs.id.isInvalid()) {
         cout << "Incoming points must have id attribute Throwing exception ..." << endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have id attribute! ", 1);
      }

   // Check for weight attribute if the user wants metaballs
   if((myPrimType == CLUSTER_PRIM_METABALL) && (myPointAttrRefs.weight.isInvalid())) {
         cout << "Incoming points must have weight attribute if instancing metaballs! Throwing exception ..." << std::endl;
         throw VRAY_clusterThis_Exception("VRAY_clusterThis::checkRequiredAttributes() Incoming points must have weight attribute if instancing metaballs!", 1);
      }


}



/* ******************************************************************************
*  Function Name : getAttributes()
*
*  Description :
*
*  Input Arguments : GEO_Point *ppt
*
*  Return Value : int
*
***************************************************************************** */
inline int VRAY_clusterThis::getAttributes(GEO_Point * ppt)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::getAttributes() " << endl;
#endif

   myPointAttributes.Cd = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.Cd, 0));
   myPointAttributes.Alpha = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.Alpha, 0));

// TODO: Use the backtrack velocity to replace velocity? Not sure ...
   if(myUseBacktrackMB)
      myPointAttributes.v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector4>(myPointAttrRefs.backtrack, 0));
   else
      myPointAttributes.v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.v, 0));

//   myPointAttributes.v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.v, 0));
   myPointAttributes.backtrack = static_cast<UT_Vector4>(ppt->getValue<UT_Vector4>(myPointAttrRefs.backtrack, 0));
   myPointAttributes.up = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.up, 0));
   myPointAttributes.N = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.N, 0));
   myPointAttributes.N.normalize();

   myPointAttributes.radius = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.radius, 0));
   myPointAttributes.vdb_radius = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.vdb_radius, 0));
   myPointAttributes.pscale = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.pscale, 0));
   myPointAttributes.width = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.width, 0));
   myPointAttributes.id = static_cast<int>(ppt->getValue<int>(myPointAttrRefs.id, 0));
   myPointAttributes.material = ppt->getString(myPointAttrRefs.material) ;
//     cout << "VRAY_clusterThis::getAttributes() myPointAttributes.material: " << myPointAttributes.material << endl;

   if(myPrimType == CLUSTER_PRIM_METABALL)
      myPointAttributes.weight = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.weight, 0));

   if(myPrimType == CLUSTER_FILE)
      myPointAttributes.geo_fname = ppt->getString(myPointAttrRefs.geo_fname) ;

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::getAttributes() " << "Cd: " << myPointAttributes.Cd << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "Alpha: " << myPointAttributes.Alpha << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "v: " << myPointAttributes.v << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "N: " << myPointAttributes.N << endl;
//   cout << "VRAY_clusterThis::getAttributes() " << "orient: " << myPointAttributes.orient << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "pscale: " << myPointAttributes.pscale << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "radius: " << myPointAttributes.radius << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "vdb_radius: " << myPointAttributes.vdb_radius << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "id: " << myPointAttributes.id << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "weight: " << myPointAttributes.weight << endl;
   cout << "VRAY_clusterThis::get_attributes() " << "material: " << myPointAttributes.material << endl;
   cout << "VRAY_clusterThis::get_attributes() " << "geo_fname: " << myPointAttributes.geo_fname << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "myMaterial: " << myMaterial << endl;
#endif

   return 0;

}




inline int VRAY_clusterThis::getAttributes2(GEO_Point * ppt, VRAY_clusterThis::pt_attr_struct *thePointAttributes)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::getAttributes() " << endl;
#endif

   thePointAttributes->Cd = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.Cd, 0));
   thePointAttributes->Alpha = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.Alpha, 0));

// TODO: Use the backtrack velocity to replace velocity? Not sure ...
   if(myUseBacktrackMB)
      thePointAttributes->v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector4>(myPointAttrRefs.backtrack, 0));
   else
      thePointAttributes->v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.v, 0));

//   thePointAttributes.v = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.v, 0));
   thePointAttributes->backtrack = static_cast<UT_Vector4>(ppt->getValue<UT_Vector4>(myPointAttrRefs.backtrack, 0));
   thePointAttributes->up = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.up, 0));
   thePointAttributes->N = static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(myPointAttrRefs.N, 0));
   thePointAttributes->N.normalize();

   thePointAttributes->radius = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.radius, 0));
   thePointAttributes->vdb_radius = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.vdb_radius, 0));
   thePointAttributes->pscale = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.pscale, 0));
   thePointAttributes->width = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.width, 0));
   thePointAttributes->id = static_cast<int>(ppt->getValue<int>(myPointAttrRefs.id, 0));
   thePointAttributes->material = ppt->getString(myPointAttrRefs.material) ;
//     cout << "VRAY_clusterThis::getAttributes() thePointAttributes.material: " << thePointAttributes.material << endl;

   if(myPrimType == CLUSTER_PRIM_METABALL)
      thePointAttributes->weight = static_cast<fpreal>(ppt->getValue<fpreal>(myPointAttrRefs.weight, 0));

   if(myPrimType == CLUSTER_FILE)
      thePointAttributes->geo_fname = ppt->getString(myPointAttrRefs.geo_fname) ;

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::getAttributes() " << "Cd: " << thePointAttributes->Cd << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "Alpha: " << thePointAttributes->Alpha << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "v: " << thePointAttributes->v << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "N: " << thePointAttributes->N << endl;
//   cout << "VRAY_clusterThis::getAttributes() " << "orient: " << thePointAttributes->orient << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "pscale: " << thePointAttributes->pscale << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "radius: " << thePointAttributes->radius << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "vdb_radius: " << thePointAttributes->vdb_radius << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "id: " << thePointAttributes->id << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "weight: " << thePointAttributes->weight << endl;
   cout << "VRAY_clusterThis::get_attributes() " << "material: " << thePointAttributes->material << endl;
   cout << "VRAY_clusterThis::get_attributes() " << "geo_fname: " << thePointAttributes->geo_fname << endl;
   cout << "VRAY_clusterThis::getAttributes() " << "myMaterial: " << myMaterial << endl;
#endif

   return 0;

}




/* ******************************************************************************
*  Function Name : addFileAttributeRefs()
*
*  Description :   Add attribute references for the instanced file
*
*  Input Arguments : GU_Detail *inst_gdp
*
*  Return Value : int status
*
***************************************************************************** */
inline int VRAY_clusterThis::addFileAttributeRefs(GU_Detail * inst_gdp)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::addFileAttributeOffsets() " << endl;
#endif

   // Primitive attributes
   myFileAttrRefs.Cd = inst_gdp->addDiffuseAttribute(GEO_PRIMITIVE_DICT);
   myFileAttrRefs.Alpha = inst_gdp->addAlphaAttribute(GEO_PRIMITIVE_DICT);
   myFileAttrRefs.v = inst_gdp->addVelocityAttribute(GEO_PRIMITIVE_DICT);
   myFileAttrRefs.N = inst_gdp->addNormalAttribute(GEO_PRIMITIVE_DICT);
//   myFileAttrRefs.id = inst_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "id", 1);
//   myFileAttrRefs.inst_id = inst_gdp->addIntTuple(GA_ATTRIB_PRIMITIVE, "inst_id", 1);
//
   myFileAttrRefs.material = inst_gdp->addStringTuple(GA_ATTRIB_PRIMITIVE, "shop_materialpath", 1);

   // Point attributes
   myFileAttrRefs.pointCd = inst_gdp->addDiffuseAttribute(GEO_POINT_DICT);
   myFileAttrRefs.Alpha = inst_gdp->addAlphaAttribute(GEO_POINT_DICT);
   myFileAttrRefs.pointV = inst_gdp->addVelocityAttribute(GEO_POINT_DICT);

//   myFileAttrRefs.pointN = inst_gdp->pointAttribs().getOffset ( "N", GB_ATTRIB_VECTOR );
//   if(myFileAttrRefs.pointN == -1)
//      myFileAttrRefs.pointN = inst_gdp->addNormalAttribute(GEO_POINT_DICT);

//   myFileAttrRefs.pointPscale = inst_gdp->addFloatTuple(GA_ATTRIB_POINT, "pscale", 1);
//   myFileAttrRefs.pointId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
//   myFileAttrRefs.pointInstId = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "inst_id", 1);
//   myFileAttrRefs.lod = inst_gdp->addIntTuple(GA_ATTRIB_POINT, "lod", 1);

   return 0;
}


/* ******************************************************************************
*  Function Name : setPointInstanceAttributes()
*
*  Description :
*
*  Input Arguments : GU_Detail *inst_gdp, GEO_Point *ppt
*
*  Return Value : void
*
***************************************************************************** */
inline void VRAY_clusterThis::setPointInstanceAttributes(GU_Detail * inst_gdp, GEO_Point * ppt,
                                                         VRAY_clusterThis::pt_attr_struct * thePointAttributes,
                                                         VRAY_clusterThis::inst_attr_ref_struct * theInstAttrRefs
                                                         )
{

assert(inst_gdp);
assert(ppt);
assert(thePointAttributes);
assert(theInstAttrRefs);

#ifdef DCA_DEBUG
   std::cout << "VRAY_clusterThis::setPointInstanceAttributes() " << std::endl;
#endif

// TODO: Determine which attibutes are *really* required for point instancing, examine shaders, perhaps add compile time switches
// user wants to have more attributes passed to the shaders.

   ppt->setValue<UT_Vector3>(theInstAttrRefs->pointCd, (const UT_Vector3)thePointAttributes->Cd);
   ppt->setValue<fpreal>(theInstAttrRefs->pointAlpha, (const fpreal)thePointAttributes->Alpha);
   ppt->setValue<UT_Vector3>(theInstAttrRefs->pointV, (const UT_Vector3)thePointAttributes->v);
   ppt->setValue<UT_Vector3>(theInstAttrRefs->pointBacktrack, (const UT_Vector3)thePointAttributes->backtrack);
   ppt->setValue<UT_Vector3>(theInstAttrRefs->pointN, (const UT_Vector3)thePointAttributes->N);
   ppt->setValue<fpreal>(theInstAttrRefs->pointRadius, (const fpreal)thePointAttributes->radius);
   ppt->setValue<fpreal>(theInstAttrRefs->pointPscale, (const fpreal)thePointAttributes->pscale);
   ppt->setValue<int>(theInstAttrRefs->pointId, (const int)thePointAttributes->id);
   ppt->setValue<int>(theInstAttrRefs->pointInstId, (const int)myInstanceNum);
   ppt->setString(theInstAttrRefs->pointMaterial, thePointAttributes->material);

//   std::cout << "VRAY_clusterThis::setPointInstanceAttributes() thePointAttributes->Cd: "
//   << thePointAttributes->Cd << " ppt Cd: " << static_cast<UT_Vector3>(ppt->getValue<UT_Vector3>(theInstAttrRefs.pointCd, 0)) << std::endl;

}


/* ******************************************************************************
*  Function Name : setInstanceAttributes()
*
*  Description : Set the attributes of the instanced primitive
*
*  Input Arguments : GEO_Primitive *myGeoPrim
*
*  Return Value : void
*
***************************************************************************** */
inline void VRAY_clusterThis::setInstanceAttributes(GEO_Primitive * myGeoPrim, VRAY_clusterThis::clusterPrimTypeEnum myPrimType)
{
#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::setInstanceAttributes() " << endl;
#endif
   GEO_Point * ppt;

//   if(myPrimType == CLUSTER_PRIM_CUBE) {
//         const UT_Vector3 red(1.0, 0.0, 0.0);
////         cout << "VRAY_clusterThis::setInstanceAttributes() CUBE!" << endl;
//         myGeoPrim->setValue<UT_Vector3>(myInstAttrRefs.Cd, red);
//         myGeoPrim->setString(myInstAttrRefs.material, myPointAttributes.material);
//
//         for(int i = 0; i < myGeoPrim->getVertexCount(); i++) {
//               ppt = myGeoPrim->getVertexElement(i).getPt();
//               ppt->setValue<UT_Vector3>(myInstAttrRefs.pointCd, red);
//               ppt->setString(myInstAttrRefs.pointMaterial, myPointAttributes.material);
//            }
//         return;
//      }

   myGeoPrim->setValue<UT_Vector3>(myInstAttrRefs.Cd, (const UT_Vector3)myPointAttributes.Cd);
   myGeoPrim->setValue<fpreal>(myInstAttrRefs.Alpha, (const fpreal)myPointAttributes.Alpha);
   myGeoPrim->setValue<UT_Vector3>(myInstAttrRefs.v, (const UT_Vector3)myPointAttributes.v);
   myGeoPrim->setValue<UT_Vector3>(myInstAttrRefs.N, (const UT_Vector3)myPointAttributes.N);
//   myGeoPrim->setValue<UT_Vector4>(myInstAttrRefs.orient, (const UT_Vector4)myPointAttributes.orient);
   myGeoPrim->setValue<fpreal>(myInstAttrRefs.radius, (const fpreal)myPointAttributes.radius);
   myGeoPrim->setValue<fpreal>(myInstAttrRefs.pscale, (const fpreal)myPointAttributes.pscale);
   myGeoPrim->setValue<int>(myInstAttrRefs.id, (const int)myPointAttributes.id);
   myGeoPrim->setValue<int>(myInstAttrRefs.inst_id, (const int)myInstanceNum);
   myGeoPrim->setString(myInstAttrRefs.material, myPointAttributes.material);

   if(myPrimType == CLUSTER_PRIM_METABALL)
      myGeoPrim->setValue<fpreal>(myInstAttrRefs.weight, (const fpreal)myPointAttributes.weight);
   if(myPrimType == CLUSTER_PRIM_CURVE)
      myGeoPrim->setValue<fpreal>(myInstAttrRefs.width, (const fpreal)myPointAttributes.width);


   // apply attributes to each vertex
   for(int i = 0; i < myGeoPrim->getVertexCount(); i++) {
         ppt = myGeoPrim->getVertexElement(i).getPt();
         ppt->setValue<UT_Vector3>(myInstAttrRefs.pointCd, (const UT_Vector3)myPointAttributes.Cd);
         ppt->setValue<float>(myInstAttrRefs.pointAlpha, (const float)myPointAttributes.Alpha);
         ppt->setValue<UT_Vector3>(myInstAttrRefs.pointV, (const UT_Vector3)myPointAttributes.v);
         ppt->setValue<UT_Vector3>(myInstAttrRefs.pointN, (const UT_Vector3)myPointAttributes.N);
//         ppt->setValue<UT_Vector3>(myInstAttrRefs.pointOrient, (const UT_Vector3)myPointAttributes.orient);
         ppt->setValue<float>(myInstAttrRefs.pointRadius, (const float)myPointAttributes.radius);
         ppt->setValue<float>(myInstAttrRefs.pointPscale, (const float)myPointAttributes.pscale);
         ppt->setValue<int>(myInstAttrRefs.pointId, (const int)myPointAttributes.id);
         ppt->setValue<int>(myInstAttrRefs.pointInstId, (const int)myInstanceNum);
         ppt->setString(myInstAttrRefs.pointMaterial, myPointAttributes.material);

         if(myPrimType == CLUSTER_PRIM_METABALL)
            ppt->setValue<float>(myInstAttrRefs.pointWeight, myPointAttributes.weight);
         if(myPrimType == CLUSTER_PRIM_CURVE)
            ppt->setValue<float>(myInstAttrRefs.pointWidth, myPointAttributes.width);

      }

}



/* ******************************************************************************
*  Function Name : setFileAttributes()
*
*  Description :
*
*  Input Arguments : GEO_Point *ppt, GU_Detail *inst_gdp
*
*  Return Value : int
*
***************************************************************************** */
inline int VRAY_clusterThis::setFileAttributes(GU_Detail * file_gdp)
{

#ifdef DCA_DEBUG
   cout << "VRAY_clusterThis::setFileAttributes() " << endl;
#endif

   GEO_Point * ppt;

#ifdef DCA_DEBUG
   long int num_points = (long int) file_gdp->points().entries();
   cout << "VRAY_clusterThis::setFileAttributes() - num points :" << num_points << endl;
#endif

// NOTE: File instanced geo should have normals already, do not set the normals to the source point normals

   GA_FOR_ALL_GPOINTS(file_gdp, ppt) {

      ppt->setValue<UT_Vector3>(myFileAttrRefs.Cd, (const UT_Vector3)myPointAttributes.Cd);
      ppt->setValue<float>(myFileAttrRefs.Alpha, (const float)myPointAttributes.Alpha);
      ppt->setValue<UT_Vector3>(myFileAttrRefs.pointV, (const UT_Vector3)myPointAttributes.v);
      ppt->setValue<int>(myFileAttrRefs.pointId, (const int)myPointAttributes.id);
      ppt->setString(myFileAttrRefs.material, myPointAttributes.material);
   }


   GEO_Primitive * prim;

   GA_FOR_ALL_PRIMITIVES(file_gdp, prim)  {

      prim->setValue<UT_Vector3>(myFileAttrRefs.Cd, (const UT_Vector3)myPointAttributes.Cd);
      prim->setValue<fpreal>(myFileAttrRefs.Alpha, (const fpreal)myPointAttributes.Alpha);
      prim->setValue<UT_Vector3>(myFileAttrRefs.v, (const UT_Vector3)myPointAttributes.v);
      prim->setValue<int>(myFileAttrRefs.id, (const int)myPointAttributes.id);
      prim->setString(myFileAttrRefs.material, myPointAttributes.material);
   }

   return 0;
}


#endif



