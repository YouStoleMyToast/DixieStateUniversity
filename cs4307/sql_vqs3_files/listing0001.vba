Sub GetAuthorNames()
  Dim db As Database
  Dim rs As Recordset
  Dim i As Integer
  Dim au_names() As String
  Set db = CurrentDb()
  Set rs = db.OpenRecordset("authors")
  rs.MoveLast
  ReDim au_names(rs.RecordCount - 1, 1)
  With rs
    .MoveFirst
    i = 0
    Do Until .EOF
      au_names(i, 0) = ![au_fname]
      au_names(i, 1) = ![au_lname]
      i = i + 1
      .MoveNext
    Loop
  End With
  rs.Close
  db.Close
End Sub
