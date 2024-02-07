int Submitter::printDueDates() {
   int bad = 0;
   string title;
   Date dueDate;
   std::stringstream ssDue;
   //cout << col_pink << "Listing " << m_asVals["assessment_name"][0] << " " << m_accommTitle << " due dates:" << col_end << endl;
   {
      // CORNEL
      cout << "Listing " << col_pink << m_asVals["assessment_name"][0] << " " << m_accommTitle << col_end
         << "important dates:" << endl;
   }
   if (m_asVals.exist("publish_date")) {
      ssDue << m_asVals["publish_date"][0];
      dueDate.read(ssDue);
      if (dueDate.bad()) {
         cout << "Error #22.1 Bad publicatoin date format in config file." << endl
            << "Please report this to your professor." << endl;
         bad = 22;
      }
      else {
         //cout << col_cyan << "Submissions are open after " << dueDate << "." << col_end << endl;
         // CORNEL
         cout << "      Open " << col_cyan << dueDate << "  ■  " << col_end << endl;
      }
   }
   if (!bad && m_asVals.exist("due_dates")) {
      int nl = m_asVals["due_dates"].size();
      int li = 0;
      bool first = true;
      if (nl % 2 == 0) {
         while (!bad && li < nl) {
            ssDue.clear();
            ssDue.str(std::string());
            ssDue << m_asVals["due_dates"][li++];
            title = m_asVals["due_dates"][li++];
            dueDate.read(ssDue);
            if (dueDate.bad()) {
               cout << "Error #20.1: bad due date format in config file." << endl
                  << "Please report this to your professor!" << endl;
               bad = 20;
            }
            else {
               dueDate += m_accommExtension;
               dueDate.addMin(m_accommExtMins);
               //if (first) {
               //   cout << col_green << "On time submission before " << dueDate << col_end << endl;
               //   first = false;
               //}
               {
                  // CORNEL
                  if (first)
                  {
                     cout << "    Before " << col_green << dueDate << "  ■→  " << col_end << "«on time»" << endl;
                     first = false;
                  }
                  cout << "     After \033[38;5;11m" << dueDate << "  ■→  " << col_end
                     << (title.length() == 0 ? string("«late»") : title) << endl;
               }
               //cout << "\033[38;5;11m" << (title.length() == 0 ? string("Late") : title) << " submission after " << dueDate << col_end << endl;
            }
         }
      }
      else {
         cout << "Error #21.1: bad due date and late title sequence in config file." << endl
            << "Please report this to your professor!" << endl;
         bad = 21;
      }
   }
   else {
      cout << col_green << "No due dates are set for this submission..." << col_end << endl;
      cout << col_red << "Please refer to the documentation of the assignment!" << col_end << endl;
   }
   ssDue.clear();
   if (!bad) {
      if (m_asVals.exist("rejection_date")) {
         ssDue << m_asVals["rejection_date"][0];
         dueDate.read(ssDue);
         dueDate += m_accommExtension;
         dueDate.addMin(m_accommExtMins);
         if (dueDate.bad()) {
            cout << "Error# 22.1Bad rejection date format in config file." << endl
               << "Please report this to your professor." << endl;
            bad = 22;
         }
         else {
            //cout << col_red << "Submissions are rejected after " << dueDate << "!" << col_end << endl;
            // CORNEL
            cout << "     Close " << col_red << dueDate << "  ■  " << col_end << endl;
         }
      }
      else {
         cout << col_green << "No rejection date is set for this submission..." << col_end << endl;
         cout << col_red << "Please refer to the documentation of the assignment!" << col_end << endl;
      }
   }
   return bad;
}