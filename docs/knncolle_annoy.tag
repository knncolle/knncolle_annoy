<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8">
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
    <templarg>class Distance_</templarg>
    <templarg>class Matrix_</templarg>
    <templarg>typename Float_</templarg>
    <templarg>typename InternalIndex_</templarg>
    <templarg>typename InternalData_</templarg>
    <base>knncolle::Builder</base>
    <member kind="function">
      <type></type>
      <name>AnnoyBuilder</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a20f4ce2cddda3dd050e76d27f62a0332</anchor>
      <arglist>(AnnoyOptions options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AnnoyBuilder</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>a326d9025842012fa999d3e0da9124bfd</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>AnnoyOptions &amp;</type>
      <name>get_options</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>aaa5e91bcc90bcc5dfa6150724d4b8af7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>knncolle::Prebuilt&lt; typename Matrix_::dimension_type, typename Matrix_::index_type, Float_ &gt; *</type>
      <name>build_raw</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyBuilder.html</anchorfile>
      <anchor>ac7eb10e0d4ce881ba44c001558338286</anchor>
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
    <templarg>class Distance_</templarg>
    <templarg>typename Dim_</templarg>
    <templarg>typename Index_</templarg>
    <templarg>typename Float_</templarg>
    <templarg>typename InternalIndex_</templarg>
    <templarg>typename InternalData_</templarg>
    <base>Prebuilt&lt; Dim_, Index_, Float_ &gt;</base>
    <member kind="function">
      <type>Dim_</type>
      <name>num_dimensions</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyPrebuilt.html</anchorfile>
      <anchor>a867140a8569539500e60e1d32aa3d3b2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Index_</type>
      <name>num_observations</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyPrebuilt.html</anchorfile>
      <anchor>a5f8c8f46151fba43dc767e96587bc349</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; knncolle::Searcher&lt; Index_, Float_ &gt; &gt;</type>
      <name>initialize</name>
      <anchorfile>classknncolle__annoy_1_1AnnoyPrebuilt.html</anchorfile>
      <anchor>aec80499e4874bd30f8aa58a3f2251018</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>knncolle_annoy::AnnoySearcher</name>
    <filename>classknncolle__annoy_1_1AnnoySearcher.html</filename>
    <templarg>class Distance_</templarg>
    <templarg>typename Dim_</templarg>
    <templarg>typename Index_</templarg>
    <templarg>typename Float_</templarg>
    <templarg>typename InternalIndex_</templarg>
    <templarg>typename InternalData_</templarg>
    <base>Searcher&lt; Index_, Float_ &gt;</base>
    <member kind="function">
      <type>void</type>
      <name>search</name>
      <anchorfile>classknncolle__annoy_1_1AnnoySearcher.html</anchorfile>
      <anchor>a3a588b6bea8c42116a27adb9212efe6f</anchor>
      <arglist>(Index_ i, Index_ k, std::vector&lt; Index_ &gt; *output_indices, std::vector&lt; Float_ &gt; *output_distances)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>search</name>
      <anchorfile>classknncolle__annoy_1_1AnnoySearcher.html</anchorfile>
      <anchor>a6d59ec98dc05ada3cbb6ebe13b9b0caa</anchor>
      <arglist>(const Float_ *query, Index_ k, std::vector&lt; Index_ &gt; *output_indices, std::vector&lt; Float_ &gt; *output_distances)</arglist>
    </member>
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
