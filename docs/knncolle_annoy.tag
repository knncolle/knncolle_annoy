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
      <type>NumericType</type>
      <name>index</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</anchorfile>
      <anchor>a3ebbe427960efa7d30fa5ffd80bdfe1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>NumericType</type>
      <name>data</name>
      <anchorfile>structknncolle__annoy_1_1AnnoyPrebuiltTypes.html</anchorfile>
      <anchor>a189a767607a3b01f203ec7eb312f883e</anchor>
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
    <member kind="enumeration">
      <type></type>
      <name>NumericType</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>ab5b68f6564b16322f9b231b4548ecd0c</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca25185a78b19f8b194e2955929e32baca">UINT8_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0caa4ce26f417237ef0667dd68d978d9193">INT8_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0cabd93e66a884d0291f3db5bb0eeb03ffe">UINT16_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca5e66c6e44fda6975bc1d1f10f4ea0436">INT16_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0cabc0d406b455d82bfc780c67be1976fed">UINT32_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca1436af9feb7b630b48ac357f5157bbca">INT32_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca1ffe86dfa4f41564147b2fb8340c883a">UINT64_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0caf9ac882f78f9c31f0a7cfb558ff6b7df">INT64_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0caa50a06389a9e2b28e818734a60a2f5b5">UNSIGNED_CHAR</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca8baa03c8db1826ac5f64e4e948bc1101">SIGNED_CHAR</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca027acd3aa6b1dd7f26119d3cf0f9a063">CHAR</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca765ef1b950ba8455b8992510ffa56895">UNSIGNED_SHORT</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0caa35c2b02966b1563e5bf7b81b8b0cf77">SHORT</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca9ba5b3da1d35e22e1680ddbe52d36ed5">UNSIGNED_INT</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca53f93baa3057821107c750323892fa92">INT</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca2a26ad8ee66f08d59e05a6c9a8e60fed">UNSIGNED_LONG</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0cac1fabfea54ec6011e694f211f3ffebf3">LONG</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca3c1f115f76d0dd87e6bc8364d9eafb6e">UNSIGNED_LONG_LONG</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca81d783829cf8f0f238c0f37194ae94cb">LONG_LONG</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca281dea8e27e21a83e47f92254e1f4d4d">SIZE_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca2b76fab4bd78a7d089445463c877ea9e">PTRDIFF_T</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0cae738c26bf4ce1037fa81b039a915cbf6">FLOAT</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0cafd3e4ece78a7d422280d5ed379482229">DOUBLE</enumvalue>
      <enumvalue file="namespaceknncolle__annoy.html" anchor="ab5b68f6564b16322f9b231b4548ecd0ca696b031073e74bf2cb98e5ef201d4aa3">UNKNOWN</enumvalue>
    </member>
    <member kind="function">
      <type>AnnoyPrebuiltTypes</type>
      <name>load_annoy_prebuilt_types</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a57a33c712b732200c7b46d36f13bfb78</anchor>
      <arglist>(const std::string &amp;prefix)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>load_annoy_prebuilt</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a480d8350b6c83729f140253ee3ca64cb</anchor>
      <arglist>(const std::string &amp;prefix)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>get_distance_name</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a0f46fd7ab22d7976baec00c98c038bea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>NumericType</type>
      <name>get_numeric_type</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a5a77303e4f9434ddc0218aa14b19f1fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::function&lt; void(const std::string &amp;)&gt; &amp;</type>
      <name>customize_save_for_annoy_types</name>
      <anchorfile>namespaceknncolle__annoy.html</anchorfile>
      <anchor>a46b2125811a26fae459c4c54803be3ae</anchor>
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
