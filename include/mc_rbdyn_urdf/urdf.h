#ifndef _H_MCRBDYNURDF_H_
#define _H_MCRBDYNURDF_H_

#include <SpaceVecAlg/SpaceVecAlg>
#include <RBDyn/Joint.h>
#include <RBDyn/MultiBody.h>
#include <RBDyn/MultiBodyConfig.h>
#include <RBDyn/MultiBodyGraph.h>
#include <Eigen/Core>
#include <tinyxml2.h>
#include <string>

namespace mc_rbdyn_urdf
{

struct Limits
{
public:
  std::map< int, std::vector<double> > lower;
  std::map< int, std::vector<double> > upper;
  std::map< int, std::vector<double> > velocity;
  std::map< int, std::vector<double> > torque;
};

struct URDFParserResult
{
public:
  rbd::MultiBody mb;
  rbd::MultiBodyConfig mbc;
  rbd::MultiBodyGraph mbg;
  mc_rbdyn_urdf::Limits limits;
  std::map<int, sva::PTransformd> visual_tf;
  std::map<int, sva::PTransformd> collision_tf;
};

std::vector<double> attrToList(const tinyxml2::XMLElement & dom, const std::string & attr, const std::vector<double> & def = {});

Eigen::Vector3d attrToVector(const tinyxml2::XMLElement & dom, const std::string & attr, const Eigen::Vector3d & def = Eigen::Vector3d(0,0,0));

Eigen::Matrix3d RPY(const double & r, const double & p, const double & y);

rbd::Joint::Type rbdynFromUrdfJoint(const std::string & type);

sva::PTransformd originFromTag(const tinyxml2::XMLElement & root, const std::string & tagName);

URDFParserResult rbdyn_from_urdf(const std::string & content, bool fixed = true, const std::vector<std::string> & filteredLinksIn = {}, bool transformInertia = true, const std::string & baseLinkIn = "", bool withVirtualLinks = true);

}

#endif
