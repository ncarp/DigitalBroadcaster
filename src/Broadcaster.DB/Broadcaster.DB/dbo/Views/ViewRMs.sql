CREATE VIEW [dbo].[ViewRMs]
AS
SELECT     dbo.RMs.ID, dbo.RMs.Name, dbo.RMs.TypeID, dbo.RMs.KeyWords, dbo.RMs.Obs, dbo.RMs.Activ, dbo.RMs.[Date], dbo.RMs.PathID, 
                      dbo.RMs.FileName, dbo.RMs.Start, dbo.RMs.Mix, dbo.RMs.Finish, dbo.RMs.DRM35, dbo.RMs.ArchiveID, dbo.TypeOfRM.Name AS Type, 
                      dbo.HD.Path AS Path
FROM         dbo.RMs INNER JOIN
                      dbo.TypeOfRM ON dbo.RMs.TypeID = dbo.TypeOfRM.ID LEFT OUTER JOIN
                      dbo.HD ON dbo.RMs.PathID = dbo.HD.ID


