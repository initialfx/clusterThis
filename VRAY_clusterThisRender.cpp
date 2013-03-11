/* ******************************************************************************
*
*  VRAY_clusterThisRender
*
*
* Description :
*
***************************************************************************** */

#ifndef __VRAY_clusterThisRender_cpp__
#define __VRAY_clusterThisRender_cpp__


/* ******************************************************************************
*  Function Name : render()
*
*  Description :   Render VRAY_clusterThis object
*
*  Input Arguments : None
*
*  Return Value : None
*
***************************************************************************** */
void VRAY_clusterThis::render()
{
//   GU_Detail * gdp;
   GU_Detail * inst_gdp, *mb_gdp, *file_gdp;
   UT_BoundingBox tmpBox;

   myRenderTime = std::clock();
   std::time(&myRenderStartTime);

   tempFileDeleted = false;
   static bool rendered = false;

//   myPasses(1);
   std::cout << "VRAY_clusterThis::render() - num_passes: " << myPasses(1) <<  std::endl;

   if(myVerbose > CLUSTER_MSG_INFO)
      cout << "VRAY_clusterThis::render() myLOD: " << myLOD << std::endl;


   if(myVerbose > CLUSTER_MSG_QUIET) {
         std::cout << "VRAY_clusterThis::render() - Instancing ..." <<  std::endl;
      }


   try {

         if(!rendered || !myUseTempFile) {

               if(myUseGeoFile) {
                     // If the file failed to load, throw an exception
                     myGdp->clearAndDestroy();
                     if(!(myGdp->load((const char *)mySrcGeoFname).success()))
//                     if(!(gdp->load((const char *)mySrcGeoFname).success()))
                        throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - Failed to read source geometry file ", 1);

                     if(myVerbose > CLUSTER_MSG_INFO)
                        cout << "VRAY_clusterThis::render() - Successfully loaded source geo file: " << mySrcGeoFname << std::endl;
                  }

               if(!myGdp) {
                     throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - object has no geometry ", 1);
                  }

               mySourceGDPMemUsage = myGdp->getMemoryUsage();

//// DEBUG
//               myGdp->getBBox(&tmpBox);
//               std::cout << "VRAY_clusterThis::render() - myGdp->getBBox(&tmpBox): " << tmpBox << std::endl;


               // Import the object:velocityscale settings.  This setting stores the
               // shutter time (in seconds) on a per object basis.  It's used primarily
               // for velocity blur.
               if(!import("object:velocityscale", &myVelocityScale, 1)) {
                     myVelocityScale = 0.5F / myFPS;
                     if(myVerbose > CLUSTER_MSG_INFO)
                        std::cout << "VRAY_clusterThis::render() did not find object:velocityscale, setting myVelocityScale to 0.0"  << std::endl;
                  }
               else {
                     if(myVerbose == CLUSTER_MSG_DEBUG)
                        std::cout << "VRAY_clusterThis::render() found object:velocityscale. myVelocityScale: " << myVelocityScale << std::endl;
                  }


               if(myVerbose > CLUSTER_MSG_QUIET)
                  cout << "VRAY_clusterThis::render() Number of points of incoming geometry: " << myNumSourcePoints << std::endl;

               inst_gdp = VRAY_Procedural::allocateGeometry();
               if(!inst_gdp) {
                     throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - error allocating geometry for inst_gdp ", 1);
                  }

               if(myDoMotionBlur == CLUSTER_MB_DEFORMATION) {
                     mb_gdp = VRAY_Procedural::allocateGeometry();
                     if(!mb_gdp) {
                           throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - error allocating geometry for mb_gdp ", 1);
                        }
                  }

               rendered = true;

               if(myPrimType == CLUSTER_FILE) {
                     file_gdp = VRAY_Procedural::allocateGeometry();
                     int file_load_stat = VRAY_clusterThis::preLoadGeoFile(file_gdp);

                     if(!file_load_stat) {
                           if(myVerbose > CLUSTER_MSG_INFO)
                              cout << "VRAY_clusterThis::render() Successfully loaded geometry file: " << myGeoFile << std::endl;
                        }
                     else {
                           throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() Failed to load geometry file ", 1);
                        }
                  }


               if(myNoiseType < 4)
                  myNoise.initialize(myNoiseSeed, static_cast<UT_Noise::UT_NoiseType>(myNoiseType));

               // Create the attribute references for the geometry to be instanced
//               VRAY_clusterThis::inst_attr_ref_struct * theInstAttrRefs;
               VRAY_clusterThis::createAttributeRefs(inst_gdp, mb_gdp, &myInstAttrRefs);

//changeSetting("surface", "constant Cd ( 1 0 0 )", "object");

               fpreal theta = (2.0 * M_PI) / myNumCopies;
//               myInstanceNum = 0;
               myInstanceNum = myNumSourcePoints * myRecursion * myNumCopies;


               if(myCVEX_Exec_pre) {
                     if(myVerbose > CLUSTER_MSG_INFO)
                        cout << "VRAY_clusterThis::render() Executing Pre Process CVEX code" << std::endl;
                     VRAY_clusterThis::runCVEX(myGdp, myGdp, myCVEXFname_pre, CLUSTER_CVEX_POINT);
                  }

               myGDPReferences.gdp = myGdp;
               myGDPReferences.inst_gdp = inst_gdp;
               myGDPReferences.mb_gdp = mb_gdp;
               myGDPReferences.file_gdp = file_gdp;
               float result = 0;
               VRAY_clusterThis::renderGenerateInstance(theta, &result);

               cout << "VRAY_clusterThis::render() result: " << result << std::endl;

               if(myVerbose > CLUSTER_MSG_QUIET && myPrimType != CLUSTER_PRIM_CURVE)
                  cout << "VRAY_clusterThis::render() Total number of instances: " << myInstanceNum << std::endl;


               // Run post processing on the instanced geometry
               if(myPostProcess) {
                     VRAY_clusterThis::postProcess(myGdp, inst_gdp, mb_gdp);
                  }

//// DEBUG
//                     myGdp->getBBox(&tmpBox);
//                     std::cout << "VRAY_clusterThis::render() - after instancing - myGdp->getBBox(&tmpBox): " << tmpBox << std::endl;
//                     inst_gdp->getBBox(&tmpBox);
//                     std::cout << "VRAY_clusterThis::render() - after instancing - inst_gdp->getBBox(&tmpBox): " << tmpBox << std::endl;
//                     if(myDoMotionBlur == CLUSTER_MB_DEFORMATION) {
//                           mb_gdp->getBBox(&tmpBox);
//                           std::cout << "VRAY_clusterThis::render() - after instancing - mb_gdp->getBBox(&tmpBox): " << tmpBox << std::endl;
//                  }


               myInstGDPMemUsage = inst_gdp->getMemoryUsage();
               if(myDoMotionBlur == CLUSTER_MB_DEFORMATION)
                  myInstMbGDPMemUsage = mb_gdp->getMemoryUsage();

               if(myVerbose > CLUSTER_MSG_QUIET)
                  if(myDoMotionBlur == CLUSTER_MB_DEFORMATION)
                     cout << "VRAY_clusterThis::render() - Memory usage(MB): " <<
                          (fpreal)(myInstGDPMemUsage + myInstMbGDPMemUsage / (1024.0 * 1024.0)) << std::endl;
                  else
                     cout << "VRAY_clusterThis::render() - Memory usage(MB): " <<
                          (fpreal)(myInstGDPMemUsage / (1024.0 * 1024.0)) << std::endl;

               if(myCVEX_Exec_post) {
                     if(myVerbose > CLUSTER_MSG_INFO)
                        cout << "VRAY_clusterThis::render() Executing Post Process CVEX code" << std::endl;
                     VRAY_clusterThis::runCVEX(inst_gdp, mb_gdp, myCVEXFname_post, CLUSTER_CVEX_POINT);
                  }
               VRAY_Procedural::openGeometryObject();
               VRAY_Procedural::addGeometry(inst_gdp, 0.0);

               if(myDoMotionBlur == CLUSTER_MB_VELOCITY)
                  VRAY_Procedural::addVelocityBlurGeometry(inst_gdp, myShutter, myShutter2);

// float    addVelocityBlurGeometry (GU_Detail *gdp, fpreal pre_blur, fpreal post_blur, const char *velocity_attribute="v")

               if(myDoMotionBlur == CLUSTER_MB_DEFORMATION)
                  VRAY_Procedural::addGeometry(mb_gdp, myShutter);

//               VRAY_Procedural::setComputeN(1);
//               VRAY_Procedural::setSurface(myMaterial);
               VRAY_Procedural::closeObject();

               // Save the geo to temp location so it doesn't have to be regenerated for a deep shadow pass, etc.
               if(myUseTempFile) {
                     cout << "VRAY_clusterThis::render() temp file: " << myTempFname << std::endl;
                     ofstream myGeoStream;
                     myGeoStream.open((const char *)myTempFname, ios_base::binary);
                     UT_Options myOptions;
                     inst_gdp->save(myGeoStream, 1, &myOptions);
                     myGeoStream.flush();
                     myGeoStream.close();
                     if(myVerbose > CLUSTER_MSG_QUIET)
                        cout << "VRAY_clusterThis::render() - Saved geometry to temp file: " << myTempFname << std::endl;
                  }

               if(myPrimType == CLUSTER_FILE)
                  VRAY_Procedural::freeGeometry(file_gdp);

               // We're done, free the original geometry
               VRAY_Procedural::freeGeometry(myGdp);

            } // if (!rendered || !myUseTempFile) ...


         // Geo has already been generated ...
         // TODO: place this block of code into it's own function, clusterThisRenderCache() (or something like that)
         else {
               if(myVerbose > CLUSTER_MSG_QUIET)
                  cout << "VRAY_clusterThis::render() - Already generated geometry, reading temp geo file: " << myTempFname << std::endl;
               inst_gdp = VRAY_Procedural::allocateGeometry();
               UT_Options myOptions;

               // If the file failed to load, throw an exception
               if((inst_gdp->load((const char *)myTempFname).success())) {
                     if(myVerbose > CLUSTER_MSG_QUIET)
                        cout << "VRAY_clusterThis::render() - Successfully loaded temp geo file: " << myTempFname << std::endl;
                  }
               else
                  throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - Failed to read temp geometry file ", 1);

               VRAY_Procedural::openGeometryObject();
               VRAY_Procedural::addGeometry(inst_gdp, 0);

               if(myDoMotionBlur == CLUSTER_MB_VELOCITY)
                  VRAY_Procedural::addVelocityBlurGeometry(inst_gdp, myShutter, myShutter2);

// float    addVelocityBlurGeometry (GU_Detail *gdp, fpreal pre_blur, fpreal post_blur, const char *velocity_attribute="v")

               if(myDoMotionBlur == CLUSTER_MB_DEFORMATION) {
                     mb_gdp = allocateGeometry();

//                if(!mb_gdp->load((const char *)myTempFname, &myOptions))
                     if((mb_gdp->load((const char *)myTempFname).success())) {
                           if(myVerbose > CLUSTER_MSG_QUIET)
                              cout << "VRAY_clusterThis::render() - Successfully loaded temp geo file for deformation motion blur: " << myTempFname << std::endl;
                        }
                     else
                        throw VRAY_clusterThis_Exception("VRAY_clusterThis::render() - Failed to read temp geometry file for geometry motion blur", 1);

                     addGeometry(mb_gdp, myShutter);
                  }

//               VRAY_Procedural::setComputeN(1);
//               VRAY_Procedural::setSurface(myMaterial);
               VRAY_Procedural::closeObject();
            }

      } // try ...


   // Process exceptions ...
   catch(VRAY_clusterThis_Exception e) {
         e.what();
         cout << "VRAY_clusterThis::render() - Exception encountered, copying incoming geometry" << std::endl << std::endl;
         if(myGdp)
            VRAY_Procedural::freeGeometry(myGdp);
         if(inst_gdp)
            VRAY_Procedural::freeGeometry(inst_gdp);
         if(myDoMotionBlur == CLUSTER_MB_DEFORMATION)
            if(mb_gdp)
               VRAY_Procedural::freeGeometry(mb_gdp);
         void * handle = queryObject(0);
         myGdp = VRAY_Procedural::allocateGeometry();
         myGdp->copy(*queryGeometry(handle, 0));
         VRAY_Procedural::openGeometryObject();
         VRAY_Procedural::addGeometry(myGdp, 0);
         closeObject();
         return;
      }


   catch(...) {
         cout << "VRAY_clusterThis::render() - Unknown exception encountered, freeing geometry and exiting" << std::endl << std::endl;
         freeGeometry(myGdp);
         freeGeometry(inst_gdp);
         if(myDoMotionBlur == CLUSTER_MB_DEFORMATION)
            freeGeometry(mb_gdp);
         return;
      }


//   myPasses(0);
   if(myVerbose == CLUSTER_MSG_DEBUG)
      std::cout << "VRAY_clusterThis::render() - num_passes: " << myPasses(0) <<  std::endl;

   if(myVerbose > CLUSTER_MSG_QUIET)
      cout << "VRAY_clusterThis::render() - Leaving render() method" << std::endl;

   std::time(&myRenderEndTime);
   myRenderExecTime = std::clock() - myRenderTime;
//   cout << "VRAY_clusterThis::render() " << "myRenderExecTime: " << myRenderExecTime << endl;

   return;
}




void VRAY_clusterThis::renderGenerateInstancePartial(float theta, float * result, const UT_JobInfo & info)

{
//   GU_Detail * inst_gdp_tmp;
//   GU_Detail * inst_gdp1;
//   GU_Detail * inst_gdp2;
   GU_Detail * foo_gdp;

//   inst_gdp1 = VRAY_Procedural::allocateGeometry();
//   inst_gdp2 = VRAY_Procedural::allocateGeometry();


   GEO_Point * ppt;
   int range_start, range_end;
   long int point_num = 0;
   struct pt_attr_struct thePointAttributes;
//   struct pt_attr_struct *thePointAttributesPtr = thePointAttributes;

   myRenderGenTime = std::clock();
   std::time(&myRenderGenStartTime);
   int job = info.job();

   if(myVerbose > CLUSTER_MSG_QUIET)
      cout << "VRAY_clusterThis::renderGenerateInstancePartial() job# " << job << std::endl;

   info.divideWork(myNumSourcePoints, range_start, range_end);

   // Get the number if points of the incoming geometery, calculate an interval for reporting the status of the instancing to the user
   long int stat_interval = (long int)(myNumSourcePoints * 0.10) + 1;


   if(range_start == 0)
      range_end = range_end - 1;

   if(myVerbose == CLUSTER_MSG_DEBUG) {
         cout << "VRAY_clusterThis::renderGenerateInstancePartial() info.job() " << info.job()
              << " info.numJobs() " << info.numJobs() << " info.nextTask (): " << info.nextTask() << std::endl;
         cout << "VRAY_clusterThis::renderGenerateInstancePartial() stat_interval: " << stat_interval
              <<  " range_start: " << range_start << " range_end: " << range_end << std::endl;
      }


   if(job == 0) {
//         inst_gdp_tmp = inst_gdp1;
         VRAY_clusterThis::createAttributeRefs(myGDPReferences.inst_gdp, foo_gdp, &myInstAttrRefs);
//         theInstAttrRefsTMP = theInstAttrRefs1;
      }

//   else {
//         inst_gdp_tmp = inst_gdp2;
//         VRAY_clusterThis::createAttributeRefs(myGDPReferences.inst_gdp, foo_gdp, &myInstAttrRefs);
////         theInstAttrRefsTMP = theInstAttrRefs2;
//      }


/// For each point of the incoming geometry

   for(; range_start < range_end; range_start++) {

         ppt = myGDPReferences.gdp->points()(range_start);
         thePointAttributes.myPos = ppt->getPos();

         // get the point's attributes
         VRAY_clusterThis::getAttributes2(ppt, &thePointAttributes);

//         cout << "VRAY_clusterThis::renderGenerateInstancePartial() job# " << job
//              << " - range_start: " << range_start
//              << " thePointAttributes.myPos: " << thePointAttributes.myPos
//              << " thePointAttributes.Cd " << thePointAttributes.Cd  << std::endl;

         uint seed = 37;
         fpreal dice;
         bool skip = false;

         if(myPrimType != CLUSTER_PRIM_CURVE) {

               // For each point, make a number of copies of and recurse a number of times for each copy ...
               for(int copyNum = 0; copyNum < myNumCopies; copyNum++) {
                     for(int recursionNum = 0; recursionNum < myRecursion; recursionNum++) {

                           // generate random number to determine to instance or not
                           dice = SYSfastRandom(seed);
                           bool(dice >= myBirthProb) ? skip = true : skip = false;
//                  cout << dice << " " << skip << std::endl;
                           seed = uint(dice * 137);

                           // Calculate the position for the next instanced object ...
                           VRAY_clusterThis::calculateNewPosition(theta, copyNum, recursionNum, &thePointAttributes);

                           if(!skip) {
                                 // Create a primitive based upon user's selection
                                 switch(myPrimType) {
                                       case CLUSTER_POINT:
                                          VRAY_clusterThis::instancePoint(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp, &thePointAttributes, &myInstAttrRefs);
                                          break;
                                       case CLUSTER_PRIM_SPHERE:
                                          VRAY_clusterThis::instanceSphere(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_PRIM_CUBE:
                                          VRAY_clusterThis::instanceCube(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_PRIM_GRID:
                                          VRAY_clusterThis::instanceGrid(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_PRIM_TUBE:
                                          VRAY_clusterThis::instanceTube(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_PRIM_CIRCLE:
                                          VRAY_clusterThis::instanceCircle(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_PRIM_METABALL:
                                          VRAY_clusterThis::instanceMetaball(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                       case CLUSTER_FILE:
                                          VRAY_clusterThis::instanceFile(myGDPReferences.file_gdp, myGDPReferences.inst_gdp, myGDPReferences.mb_gdp);
                                          break;
                                    }

                              } // if(!skip) ...
                        } // for number of recursions ...
                  } // for number of copies ...
            } // if(myPrimType != CLUSTER_PRIM_CURVE) ...

         // User wants a curve instanced on this point
         if((myPrimType == CLUSTER_PRIM_CURVE) && (!skip))
            VRAY_clusterThis::instanceCurve(myGDPReferences.inst_gdp, myGDPReferences.mb_gdp, theta, point_num);

         // Increment our point counter
         point_num++;

         // Print out stats to the console
         if(myVerbose > CLUSTER_MSG_INFO && (myPrimType != CLUSTER_PRIM_CURVE))
            if((long int)(point_num % stat_interval) == 0)
               cout << "VRAY_clusterThis::renderGenerateInstancePartial() - job# " << job << " Number of points processed: "
                    << point_num << " Number of instances: " << myInstanceNum << std::endl;

      } // for all points ...


   {
      UT_AutoJobInfoLock lock_file(info);

//     cout << "VRAY_clusterThis::renderGenerateInstancePartial() - job# " << job << " LOCK a: " << a << std::endl;

      *result += point_num;
      cout << "VRAY_clusterThis::renderGenerateInstancePartial() - job# " << job
           << " XXXXXXXXXXXXXXXXXXXXXX *result: " << *result << std::endl;
//      sleep(5);
   }

//   myGDPReferences.inst_gdp->merge(*inst_gdp1);
//   if(job == 1)
//      myGDPReferences.inst_gdp->merge(*inst_gdp2);
//   myGDPReferences.mb_gdp.merge;

//   cout << "VRAY_clusterThis::renderGenerateInstancePartial() - job# " << job << " merged geometry"  << std::endl;
//
//
//   if(inst_gdp1)
//      VRAY_Procedural::freeGeometry(inst_gdp1);
//   if(inst_gdp2)
//      VRAY_Procedural::freeGeometry(inst_gdp2);
//
//   cout << "VRAY_clusterThis::renderGenerateInstancePartial() - job# " << job << " freeGeometry()"  << std::endl;

   std::time(&myRenderGenEndTime);
   myRenderGenExecTime = std::clock() - myRenderGenTime;

   cout << "VRAY_clusterThis::renderGenerateInstancePartial() - Finished " << std::endl;

}

#endif







