CREATE VIEW [dbo].[ViewJinglesData]
AS
SELECT     Broadcaster.dbo.Jingles.ID, Broadcaster.dbo.Jingles.TypeID, Broadcaster.dbo.Jingles.Rythm, 
                      Broadcaster.dbo.Jingles.Finish - Broadcaster.dbo.Jingles.Start AS Length, Broadcaster.dbo.Jingles.Name, Broadcaster.dbo.TypeOfJingle.Name AS Type
FROM         Broadcaster.dbo.Jingles INNER JOIN
                      Broadcaster.dbo.TypeOfJingle ON Broadcaster.dbo.Jingles.TypeID = Broadcaster.dbo.TypeOfJingle.ID
