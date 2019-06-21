CREATE VIEW [dbo].[ViewJinglesData_OnAir]
AS
SELECT     dbo.Jingles.ID, dbo.Jingles.TypeID, dbo.Jingles.Name, dbo.Jingles.Rythm, dbo.Jingles.Start, dbo.Jingles.Intro, dbo.Jingles.Mix, dbo.Jingles.Finish, 
                      dbo.Jingles.LoopA, dbo.Jingles.LoopB, dbo.Jingles.FileName, dbo.HD.Path, dbo.TypeOfJingle.Name AS TypeName, dbo.Jingles.Activ, 
                      dbo.Jingles.Ready, dbo.Jingles.PathID
FROM         dbo.Jingles INNER JOIN
                      dbo.HD ON dbo.Jingles.PathID = dbo.HD.ID INNER JOIN
                      dbo.TypeOfJingle ON dbo.Jingles.TypeID = dbo.TypeOfJingle.ID


