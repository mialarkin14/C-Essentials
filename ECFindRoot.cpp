// This function returns the smallest non-negative integral root of a polynomial (as specified by a list of coefficients and degree) that is no larger than xmax. Return -1 if there is no roots within the range.
//To be specific: for each integer 0 <=i <= degree, listCoeffs[d] = the coefficient of the degree d term. For example, 
int ECFindRoot(int *listCoeffs, int degree, int xmax)
{
  // listCoeffs: pointer to the array of integers as the coefficients of a polynomial; listCoeffs[0] is the constant term and so on
  // degree: highest degree term. That is, the number of coefficients in the array = degree+1
  // xmax: the largest value of root to search
  // your code here

  // loop through each integer up to the xmax and test if it evaluates to 0 in the polynomial
  for (int posRoot = 0; posRoot<= xmax; posRoot++) 
  {
      int polResult = 0;
      // try int posRoot in the polynomial and save the result in polResult
      for (int i = degree; i >= 0; i--) 
      {
          polResult = polResult * posRoot + listCoeffs[i];
      }

      // If polResult equals zero then that means posRoot is actually a root and it is the smallest root that is 
      // less than xmax because we start posRoot at 0
      if (polResult == 0) 
      {
          return posRoot; 
      }
  }
    // there was no root within range
    return -1;
}