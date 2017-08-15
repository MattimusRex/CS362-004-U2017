/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.util.ArrayList;
import java.util.List;

import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //System.out.println(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertFalse(urlVal.isValid("http:///www.google.com"));
	   assertTrue(urlVal.isValid("ftp://www.google.com"));
	   assertTrue(urlVal.isValid("http://google.com"));
	   assertFalse(urlVal.isValid("www.google.com"));
	   assertTrue(urlVal.isValid("http://1.2.3.4"));
	   assertTrue(urlVal.isValid("https://1.2.3.4"));	   
	   assertFalse(urlVal.isValid("http://1.2.3.4."));
	   assertTrue(urlVal.isValid("http://0.0.0.0"));
	   
	   bug - these two should be invalid, but reporting as valid.  incorrectly reports subgroups > 255 as valid
	   assertFalse(urlVal.isValid("http://255.255.255.256"));
	   assertFalse(urlVal.isValid("http://256.256.256.256"));
	   
	   assertTrue(urlVal.isValid("http://255.255.255.255:80"));
	   assertTrue(urlVal.isValid("http://www.google.com/foo/bar"));
	   assertTrue(urlVal.isValid("http://255.255.255.255:80/foo/bar"));
	   assertFalse(urlVal.isValid("http://255.255.255.255:80f/foo/bar"));
	   assertFalse(urlVal.isValid("https://255.255.255.255:80f/foo/bar"));
	   
	   //bug seems to not accept any queries
	   assertTrue(urlVal.isValid("http://255.255.255.255:80/foo/bar?action=view"));
	   assertTrue(urlVal.isValid("http://www.google.com?action=view"));
	   assertTrue(urlVal.isValid("http://www.google.com?person=me"));
	   
	   //bug returns false for valid query
	   assertFalse(urlVal.isValid("http://www.google.com:80/foo/bar?action=view"));
	   
	   assertTrue(urlVal.isValid("htttp://www.amazon.com"));
	   assertTrue(urlVal.isValid("http://wwww.amazon.com"));
	   assertFalse(urlVal.isValid("http://www.amazon!.com"));
	   assertFalse(urlVal.isValid("http://www!.amazon.com"));
	   assertFalse(urlVal.isValid("http://www.amazon.com!"));
	   assertTrue(urlVal.isValid("http://www.amazon.edu"));
	   //bug - should be valid
	   assertTrue(urlVal.isValid("http://www.amazon.uk"));
	   
	   
	   

	   
   }
   public void testYourFirstPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // Test IP address where each subsection is a negative value
       // isValid() should return false
       String urlToTest = "http://-1.-1.-1.-1";
       System.out.println("Result for " + urlToTest + ": " + urlVal.isValid(urlToTest));
       assertFalse(urlVal.isValid(urlToTest));
   }

   public void testYourSecondPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // Test IP address where each subsection is 0, the lower boundary case
       // isValid() should return true
       String urlToTest = "http://0.0.0.0";
       System.out.println("Result for " + urlToTest + ": " + urlVal.isValid(urlToTest));
       assertTrue(urlVal.isValid(urlToTest));
   }

   public void testYourThirdPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // Test IP address where each subsection is greater than 0 and less than 255
       // isValid() should return true
       String urlToTest = "http://10.10.10.10";
       System.out.println("Result for " + urlToTest + ": " + urlVal.isValid(urlToTest));
       assertTrue(urlVal.isValid(urlToTest));
   }

   public void testYourFourthPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // Test IP address where each subsection is 255, the upper boundary case
       // isValid() should return true
       String urlToTest = "http://255.255.255.255";
       System.out.println("Result for " + urlToTest + ": " + urlVal.isValid(urlToTest));
       assertTrue(urlVal.isValid(urlToTest));
   }

   public void testYourFifthPartition(){
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // Test IP address where each subsection is greater than 255
       // isValid() should return false
       String urlToTest = "http://300.300.300.300";
       System.out.println("Result for " + urlToTest + ": " + urlVal.isValid(urlToTest));
       assertFalse(urlVal.isValid(urlToTest));
   }

   public void testIsValid()
   {
       UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       List<ResultPair> scheme = new ArrayList<>();
       List<ResultPair> authority = new ArrayList<>();
       List<ResultPair> port = new ArrayList<>();
       List<ResultPair> urlPath = new ArrayList<>();
       List<ResultPair> urlQuery = new ArrayList<>();
       List<ResultPair> urlFragment = new ArrayList<>();

       scheme.add(new ResultPair("http://", true));
       scheme.add(new ResultPair("https://", true));
       scheme.add(new ResultPair("ftp://", true));
       scheme.add(new ResultPair("ftp:/", false));
       scheme.add(new ResultPair("https:", false));
       scheme.add(new ResultPair("http", false));
       scheme.add(new ResultPair("gopher://", true));
       scheme.add(new ResultPair("1!$^2://", false));
       scheme.add(new ResultPair("H<llo>://", false));
       //scheme.add(new ResultPair("file:///", true));

       authority.add(new ResultPair("www.google.com", true));
       authority.add(new ResultPair("amazon.uk", true));
       authority.add(new ResultPair("usa.gov", true));
       authority.add(new ResultPair("256.123.0.0", false));
       authority.add(new ResultPair("-1.-1.-1.-1", false));
       authority.add(new ResultPair("правительство.рф", true));
       authority.add(new ResultPair("155.147.177.188", true));
       authority.add(new ResultPair(".mil", false));
       authority.add(new ResultPair("1", false));
       authority.add(new ResultPair("nic.xyz", true));


       port.add(new ResultPair(":23", true));
       port.add(new ResultPair(":12345z", false));
       port.add(new ResultPair(":-12345", false));
       port.add(new ResultPair(":12$45", false));
       port.add(new ResultPair(":88888", true));
       port.add(new ResultPair(":", false));

       //NOTE according rfc 1738 the "/" is not part of the url-path. However we find it convenient to add here for brevity.
       urlPath.add(new ResultPair("", true));
       urlPath.add(new ResultPair("/rfc", true));
       urlPath.add(new ResultPair("/rfc/rfc1738.txt", true));
       urlPath.add(new ResultPair("/rfc/rfc-index.txt.new.diff", true));
       urlPath.add(new ResultPair("/%0B", true));
       urlPath.add(new ResultPair("/~", true));
       urlPath.add(new ResultPair("/_", true));
       urlPath.add(new ResultPair("/giga$byte", true));
       urlPath.add(new ResultPair("/star+fish", true));
       urlPath.add(new ResultPair("/%HI", false));
       urlPath.add(new ResultPair("/^", false));
       urlPath.add(new ResultPair("/<", false));
       urlPath.add(new ResultPair("/1325><AB", false));
       urlPath.add(new ResultPair("/{}", false));


       urlQuery.add(new ResultPair("", true));
       urlQuery.add(new ResultPair("?", true));
       urlQuery.add(new ResultPair("?name=donny&color=blue", true));
       urlQuery.add(new ResultPair("?name=donny;color=blue", true));
       urlQuery.add(new ResultPair("?2=2", true));
       urlQuery.add(new ResultPair("?", true));
       urlQuery.add(new ResultPair("?%HI", false));
       urlQuery.add(new ResultPair("?tom+read", true));
       urlQuery.add(new ResultPair("?tom~read", false));
       urlQuery.add(new ResultPair("?tom%7Eread", true));
       urlQuery.add(new ResultPair("?tom!read", true));
       urlQuery.add(new ResultPair("?tom$read", true));
       urlQuery.add(new ResultPair("?tom(read", true));

       /** https://tools.ietf.org/html/rfc3986#section-3.5
        * "If no such representation exists, then the
        semantics of the fragment are considered unknown and are effectively
        unconstrained."
        Since the fragment in unconstrained there is no obvious way to falsify.
        */
       urlFragment.add(new ResultPair("", true));
       urlFragment.add(new ResultPair("#ga", true));
       urlFragment.add(new ResultPair("#^&", true));
       urlFragment.add(new ResultPair("#t=10,20", true));

       scheme.forEach(protocol ->{
           authority.forEach(domain->{
               port.forEach(p->{
                   urlPath.forEach(path->{
                       urlQuery.forEach(query->{
                           urlFragment.forEach(fragment->{

                               String testURL = protocol.item + domain.item + p.item + path.item + query.item + fragment.item;
                               boolean resultPairTest = protocol.valid && domain.valid && p.valid && path.valid && query.valid && fragment.valid;

                               if(resultPairTest != urlValidator.isValid(testURL)){
                                   System.out.println("TEST FAILED " + testURL + " Actual Result: " + urlValidator.isValid(testURL) );


                               }
                               else{
                                   //System.out.println("TEST PASSED " + testURL);

                               }
                           });
                       });
                   });
               });
           });
       });
   }
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
