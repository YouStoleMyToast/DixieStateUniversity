Sub GetAuthorNames2()
  Dim db As Database
  Dim rs As Recordset
  Set db = CurrentDb()
  Set rs = db.OpenRecordset("SELECT au_fname, au_lname FROM authors;")
  ' --Do something with rs here.
  rs.Close
  db.Close
End Sub
