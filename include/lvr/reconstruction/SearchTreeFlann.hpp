/*
 * SearchTreeFlann.hpp
 *
 *  Created on: Sep 22, 2015
 *      Author: Thomas Wiemann
 */

#ifndef INCLUDE_LIBLVR_RECONSTRUCTION_SEARCHTREEFLANN_HPP_
#define INCLUDE_LIBLVR_RECONSTRUCTION_SEARCHTREEFLANN_HPP_

// C++ Stl includes
#include <vector>

#include <flann/flann.hpp>
#include <boost/shared_ptr.hpp>

#include <lvr/reconstruction/SearchTree.hpp>
#include <lvr/io/Timestamp.hpp>


using std::vector;

namespace lvr {

/**
 * @brief SearchClass for point data.
 *
 *      This class uses the FLANN ( http://www.cs.ubc.ca/~mariusm/uploads/FLANN )
 *      library to implement a nearest neighbour search for point-data.
 */
template< typename VertexT >
class SearchTreeFlann : public SearchTree< VertexT>
{
public:

    typedef boost::shared_ptr< SearchTreeFlann< VertexT> > Ptr;


    /**
     *  @brief Constructor. Takes the point-data and initializes the underlying searchtree.
     *
     *  @param loader  A PointBuffer point that holds the data.
     *  @param kn      The number of neighbour points used for normal estimation.
     *  @param ki      The number of neighbour points used for normal interpolation.
     *  @param kd      The number of neighbour points esed for distance value calculation.
     */
    SearchTreeFlann( PointBufferPtr points,
            size_t &n_points,
            const size_t &kn = 10,
            const size_t &ki = 10,
            const size_t &kd = 10 );


    /**
     * @brief Destructor
     */
    virtual ~SearchTreeFlann();


    /**
     * @brief This function performs a k-next-neightbour search on the
                     data that were given in the conrstructor.

     * @param qp          A float array which contains the query point for which the neighbours are searched.
     * @param neighbours  The number of neighbours that should be searched.
     * @param indices     A vector that stores the indices for the neighbours whithin the dataset.
     * @param distances   A vector that stores the distances for the neighbours that are found.
     */
    virtual void kSearch( coord < float >& qp, size_t neighbours, vector< size_t > &indices, vector< float > &distances );

    virtual void kSearch( VertexT qp, size_t k, vector< VertexT > &neighbors );

    virtual void radiusSearch( float              qp[3], float r, vector< size_t > &indices );
    virtual void radiusSearch( VertexT&              qp, float r, vector< size_t > &indices );
    virtual void radiusSearch( const VertexT&        qp, float r, vector< size_t > &indices );
    virtual void radiusSearch( coord< float >&       qp, float r, vector< size_t > &indices );
    virtual void radiusSearch( const coord< float >& qp, float r, vector< size_t > &indices );

protected:

    /// Pointer to the FLANN search tree structure
    boost::shared_ptr<flann::Index<flann::L2_Simple<float> > > 		m_tree;

    /// FLANN matrix representation of the points
    flann::Matrix<float>  	 										m_flannPoints;

    vector<size_t>													m_ind;
    vector<float>													m_dst;


}; // SearchTreeFlann

}

#include "SearchTreeFlann.tcc"

#endif /* INCLUDE_LIBLVR_RECONSTRUCTION_SEARCHTREEFLANN_HPP_ */
