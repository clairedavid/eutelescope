// -*- mode: c++; mode: auto-fill; mode: flyspell-prog; -*-
/*
 *   This source code is part of the Eutelescope package of Marlin.
 *   You are free to use this source files for your own development as
 *   long as it stays in a public research context. You are not
 *   allowed to use it for commercial purpose. You must put this
 *   header with author names in all development based on this file.
 *
 */

#ifndef EUTELVIRTUALCLUSTER_H
#define EUTELVIRTUALCLUSTER_H

// personal includes ".h"
#include "EUTELESCOPE.h"

// lcio includes <.h>
#include <IMPL/TrackerDataImpl.h>

// system includes <>
#include <iostream>

namespace eutelescope {


  //! Virtual class to describe cluster in the EUTelescope framework
  /*! There are several ways to define a clusters especially, but not
   *  only depending on the cluster search algorithm used. In order to
   *  exploit object orientation and easiness to use, all different
   *  kinds of cluster used within the EUTelescope framework are
   *  inherithing from this virtual class.
   *
   *  @Author Antonio Bulgheroni, INFN <mailto:antonio.bulgheroni@gmail.com>
   *  @Version $Id: EUTelVirtualCluster.h,v 1.7 2007-07-09 10:23:40 bulgheroni Exp $
   */

  class EUTelVirtualCluster {

  public:
    //! Default constructor
    EUTelVirtualCluster(IMPL::TrackerDataImpl *) { } 

    //! Default destructor
    virtual ~EUTelVirtualCluster() {;}
    
    //! Return the detector ID
    /*! This number is used to link the detector which this cluster
     *  belongs to the geometry description in the GEAR description.
     *
     *  @return The detector ID.
     */ 
    virtual int  getDetectorID() const                                    = 0;

    //! Return the cluster ID
    /*! This number is used to enumerate clusters.
     *
     *  @return The cluster ID.
     */ 
    virtual int  getClusterID() const                                     = 0;

    //! Get the seed pixel coordinate in the local FoR
    /*! Regardless the kind of cluster in use, it is always possible
     *  to define the seed pixel as the one with the highest signal. 
     *
     *  @param xSeed The coordinate along x of the seed pixel in the
     *  local frame of reference
     *  @param ySeed The coordinate along y of the seed pixel in the
     *  local frame of reference
     */ 
    virtual void getSeedCoord(int& xSeed, int& ySeed)  const              = 0;

    //! Get the cluster dimensions
    /*! For each cluster type is always possible to define the
     *  external sizes. 
     *
     *  @param xSize The size along x
     *  @param ySize The size along y
     */ 
    virtual void getClusterSize(int& xSize, int& ySize) const             = 0;

    //! Return the cluster quality
    /*! It returns the cluster quality using the ClusterQuality enum.
     *  
     *  @return The cluster quality
     *
     *  @see eutelescope::ClusterQuality
     */
    virtual ClusterQuality getClusterQuality() const                      = 0;

    //! Return the distance from another 
    /*! This method return the distance between this and another
     *  cluster 
     *
     *  @param  clu The other cluster
     *  @return The distance between @a this and @a clu
     */ 
    virtual float getDistance(EUTelVirtualCluster* clu) const             = 0;

    //! Return the radius of the external circle
    /*!
     *  @return The radius of the external circle
     */ 
    virtual float getExternalRadius() const                               = 0;

    //! Return the total charge
    /*!
     *  @return The total integrated charge
     */
    virtual float getTotalCharge() const                                  = 0;
    
    //! Return the seed pixel charge
    /*! 
     *  @return the charge of the seed pixel
     */ 
    virtual float getSeedCharge() const                                   = 0;

    //! Return the charge of cluster with N pixels
    /*! This method can be used to return the charge integrated into
     *  the cluster when only considering the N most significant
     *  pixels.
     *
     *  @return the charge of cluster with N pixels
     *  @param nPixel The number of pixels to consider
     */ 
    virtual float getClusterCharge(int nPixel) const                      = 0;

    //! Calculate the cluster charge with different number of pixels
    /*! This method is a better and faster replacement of the
     *  getClusterCharge(int) method. This one is actually avoiding to
     *  re-sort the signal vector all the times it is called. 
     *
     *  @param nPixels The list of number of pixels
     *  @return The charges for each number of pixels
     */ 
    virtual std::vector<float > getClusterCharge(std::vector<int > nPixels) const 
                                                                      = 0;

    //! Return the charge of a subset of the cluster
    /*! Whatever shape the cluster has it is always possible to define
     *  a rectangular frame centered on the seed pixel. With this
     *  method the charge of this frame is calculated.
     *
     *  @param  xSize Odd number to define the x size of the subframe
     *  @param  ySize Odd number to define the y size of the subframe
     *  @return The charge of the cluster subframe
     */ 
    virtual float getClusterCharge(int xSize, int ySize) const            = 0; 

    //! Return the center of gravity shift from the seed coordinates
    /*! Having a charge distribution it is possible to calculate the
     *  charge center of gravity of the cluster. This will not
     *  correspond to the center of the cluster. This method returns
     *  the shift in both directions one has to apply to the cluster
     *  center to find the center of gravity
     *
     *  @param x Shift along x
     *  @param y Shift along y
     */ 
    virtual void  getCenterOfGravityShift(float& x, float& y) const       = 0;

    //! Return the CoG shift using only a subregion of the cluster
    /*! As the method above, but this uses only a subset of pixel in
     *  the cluster: the one belonging to a frame @a xSize width @a
     *  ySize long around the center
     *
     *  @param x Shift along x
     *  @param y Shift along y
     *  @param xSize Frame size along x
     *  @param ySize Frame size along y
     */ 
    virtual void  getCenterOfGravityShift(float& x, float& y, 
					  int xSize, int ySize) const     = 0;
    
    //! Return the CoG shift using only the nth higher pixels
    /*! As the above method, but this uses only the @n pixels with the
     *  highest signal for CoG calculation
     *
     *  @param x Shift along x
     *  @param y Shift along y
     *  @param n Number of pixels to be used
     */
    virtual void  getCenterOfGravityShift(float& x, float& y,
					  int n) const                    = 0;

    //! Return the CoG coordinates
    /*! This method adds already to the shift the coordinates of the
     *  cluster center
     *
     *  @param x CoG coordinate along x
     *  @param y CoG coordinate along y
     */ 
    virtual void  getCenterOfGravity(float& x, float& y) const            = 0;
    
    //! Set the cluster quality
    /*! Used to set the cluster quality using the ClusterQuality enum.
     *  
     *  @see eutelescope::ClusterQuality
     */
    virtual void setClusterQuality(ClusterQuality)                        = 0;
    
    //! Return a pointer to the TrackerDataImpl
    /*! This method is used to expose to the public the
     *  TrackerDataImpl member.
     *
     *  @return The pointer of _trackerData
     */
    virtual IMPL::TrackerDataImpl * trackerData()                         = 0;

    //! Print
    /*! This method is used to print out the content of the clusters
     * 
     *  @param os The input output stream
     */
    virtual void print(std::ostream& os) const                            = 0;
      
    //! Overload of operator<<
    /*! This friend function is the overload of the operator << for
     *  the virtual cluster class. It uses the print method that is
     *  virtually defined for all cluster subclasses.
     *
     *  @param os The input output stream as modified by the print
     *  method
     *  @param clu The cluster to be stream out
     *  @return The output stream
     */ 
    friend std::ostream& operator<< (std::ostream& os , const EUTelVirtualCluster & clu )  { clu.print(os); return os; }

  protected:
    
    //! The tracker data member
    /*! This is the core of the decorator pattern design. Whenever an
     *  object deriving from this virtual class is created from an
     *  already existing TrackerData object, this is assigned to
     *  _trackerData by the constructor. 
     */ 
    IMPL::TrackerDataImpl * _trackerData;

  };

}

#endif
