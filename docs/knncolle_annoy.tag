<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
  <compound kind="file">
    <name>knncolle_annoy.hpp</name>
    <path>/github/workspace/include/knncolle_annoy/</path>
    <filename>knncolle__annoy_8hpp.html</filename>
    <includes id="load__annoy__prebuilt_8hpp" name="load_annoy_prebuilt.hpp" local="yes" import="no" module="no" objc="no">load_annoy_prebuilt.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="yes" import="no" module="no" objc="no">utils.hpp</includes>
    <namespace>knncolle_annoy</namespace>
  </compound>
  <compound kind="file">
    <name>load_annoy_prebuilt.hpp</name>
    <path>/github/workspace/include/knncolle_annoy/</path>
    <filename>load__annoy__prebuilt_8hpp.html</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="yes" import="no" module="no" objc="no">utils.hpp</includes>
    <class kind="struct">knncolle_annoy::AnnoyPrebuiltTypes</class>
    <namespace>knncolle_annoy</namespace>
  </compound>
  <compound kind="file">
    <name>utils.hpp</name>
    <path>/github/workspace/include/knncolle_annoy/</path>
    <filename>utils_8hpp.html</filename>
    <namespace>knncolle_annoy</namespace>
  </compound>
  <compound kind="class">
    <name>knncolle_annoy::AnnoyBuilder</name>
    <filename>classknncolle__annoy_1_1AnnoyBuilder.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class AnnoyDistance_</templarg>
    <templarg>typename AnnoyIndex_</templarg>
    <templarg>typename AnnoyData_</templarg>
    <templarg>class AnnoyRng_</templarg>
    <templarg>class AnnoyThreadPolicy_</templarg>
    <templarg>class Matrix_</templarg>
    <base>knncolle::Builder&lt; typename Index_, typename Data_, typename Distance_, class Matrix_ &gt;</base>
    <member kind="function">
      <type></type>
      <name>AnnoyBuilder</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a3af65d7b88c5b9801d06c5fc2ceb8a75</anchor>
      <arglist>(AnnoyOptions options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AnnoyBuilder</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a7e5b30a68c3c208104b769b02cb446c7</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>AnnoyOptions &amp;</type>
      <name>get_options</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a45abac40b562d4aa23e89b0eae298dd0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_raw</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a9c2ddf11d516555b458b1dad3306102d</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_unique</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a39cd70c3a33db9b2700cb0da079e041d</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_shared</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>aeb1e5d4f935173899a8cc98b7bdb6684</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>knncolle_annoy::AnnoyOptions</name>
    <filename>structknncolle__annoy_1_1AnnoyOptions.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>num_trees</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyOptions.html</anchorfile>
      <anchor>a4acbbbebaf5b5eb0d2496faefe7ee932</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>search_mult</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyOptions.html</anchorfile>
      <anchor>a7e917640043724d3933318a4504e65a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>knncolle_annoy::AnnoyPrebuiltTypes</name>
    <filename>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</filename>
    <member kind="variable">
      <type>knncolle::NumericType</type>
      <name>index</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</anchorfile>
      <anchor>ad0be50f762bae2c3fe87218ce7b0abeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>knncolle::NumericType</type>
      <name>data</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</anchorfile>
      <anchor>af7828040b51e6091600af403d19b0acc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>distance</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</anchorfile>
      <anchor>a06aaf2f6d1337bf71175ffc35a45ded2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>knncolle_annoy</name>
    <filename>namespaceknncolle__annoy.html</filename>
    <class kind="class">knncolle_annoy::AnnoyBuilder</class>
    <class kind="struct">knncolle_annoy::AnnoyOptions</class>
    <class kind="struct">knncolle_annoy::AnnoyPrebuiltTypes</class>
    <member kind="function">
      <type>AnnoyPrebuiltTypes</type>
      <name>load_annoy_prebuilt_types</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a9eff16d6db0a482607ada4d00b00c3d1</anchor>
      <arglist>(const std::filesystem::path &amp;dir)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>load_annoy_prebuilt</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a7869865e7f1417bd6fdcad52a7a66303</anchor>
      <arglist>(const std::filesystem::path &amp;dir)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>get_distance_name</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a0f46fd7ab22d7976baec00c98c038bea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::function&lt; void(const std::filesystem::path &amp;)&gt; &amp;</type>
      <name>custom_save_for_annoy_index</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a8525f55e793e3e117e404d324b519799</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::function&lt; void(const std::filesystem::path &amp;)&gt; &amp;</type>
      <name>custom_save_for_annoy_data</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a8c1f7d1200d1be4a1a3403bd9a0f91e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::function&lt; void(const std::filesystem::path &amp;)&gt; &amp;</type>
      <name>custom_save_for_annoy_distance</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>afbfa92fc904c2ed19bb8f51b50403881</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>knncolle bindings for Annoy</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
