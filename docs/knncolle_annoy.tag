<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
  <compound kind="file">
    <name>knncolle_annoy.hpp</name>
    <path>/github/workspace/include/knncolle_annoy/</path>
    <filename>knncolle__annoy_8hpp.html</filename>
    <class kind="struct">knncolle_annoy::AnnoyOptions</class>
    <class kind="class">knncolle_annoy::AnnoySearcher</class>
    <class kind="class">knncolle_annoy::AnnoyPrebuilt</class>
    <class kind="class">knncolle_annoy::AnnoyBuilder</class>
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
      <type>knncolle::Prebuilt&lt; Index_, Data_, Distance_ &gt; *</type>
      <name>build_raw</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a60c62ec5f4fdf5252169de7400b97871</anchor>
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
  <compound kind="class">
    <name>knncolle_annoy::AnnoyPrebuilt</name>
    <filename>classknncolle__annoy_1_1AnnoyPrebuilt.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class AnnoyDistance_</templarg>
    <templarg>typename AnnoyIndex_</templarg>
    <templarg>typename AnnoyData_</templarg>
    <templarg>class AnnoyRng_</templarg>
    <templarg>class AnnoyThreadPolicy_</templarg>
    <base>knncolle::Prebuilt&lt; Index_, Data_, Distance_ &gt;</base>
    <member kind="function">
      <type>std::unique_ptr&lt; knncolle::Searcher&lt; Index_, Data_, Distance_ &gt; &gt;</type>
      <name>initialize</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyPrebuilt.html</anchorfile>
      <anchor>a2a92789ec49711ac6852a721e396e105</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>knncolle_annoy::AnnoySearcher</name>
    <filename>classknncolle__annoy_1_1AnnoySearcher.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class AnnoyDistance_</templarg>
    <templarg>typename AnnoyIndex_</templarg>
    <templarg>typename AnnoyData_</templarg>
    <templarg>class AnnoyRng_</templarg>
    <templarg>class AnnoyThreadPolicy_</templarg>
    <base>knncolle::Searcher&lt; Index_, Data_, Distance_ &gt;</base>
  </compound>
  <compound kind="namespace">
    <name>knncolle_annoy</name>
    <filename>namespaceknncolle__annoy.html</filename>
    <class kind="class">knncolle_annoy::AnnoyBuilder</class>
    <class kind="struct">knncolle_annoy::AnnoyOptions</class>
    <class kind="class">knncolle_annoy::AnnoyPrebuilt</class>
    <class kind="class">knncolle_annoy::AnnoySearcher</class>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>knncolle bindings for Annoy</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
