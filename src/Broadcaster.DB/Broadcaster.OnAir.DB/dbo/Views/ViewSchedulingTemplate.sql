CREATE VIEW [dbo].[ViewSchedulingTemplate]
AS
SELECT     dbo.SchedulingTemplate.ID, dbo.SchedulingTemplate.Type, dbo.SchedulingTemplate.Name, Broadcaster.dbo.Categories.Name AS CategoryName, 
                      dbo.SchedulingTemplate.Category, dbo.SchedulingTemplate.PlayList, dbo.[PlayLists-Def].Name AS PlayListName, 
                      dbo.SchedulingTemplate.Expression, Broadcaster.dbo.Languages.Name AS ExpressionName, dbo.SchedulingTemplate.MinRythm, 
                      dbo.SchedulingTemplate.MaxRythm, dbo.SchedulingTemplate.MinLen, dbo.SchedulingTemplate.MaxLen, dbo.SchedulingTemplate.ArtistQuarantine, 
                      dbo.SchedulingTemplate.SongQuarantine, dbo.SchedulingTemplate.RandomFactor, dbo.SchedulingTemplate.LastPos
FROM         dbo.SchedulingTemplate LEFT OUTER JOIN
                      Broadcaster.dbo.Categories ON dbo.SchedulingTemplate.Category = Broadcaster.dbo.Categories.ID LEFT OUTER JOIN
                      Broadcaster.dbo.Languages ON dbo.SchedulingTemplate.Expression = Broadcaster.dbo.Languages.ID LEFT OUTER JOIN
                      dbo.[PlayLists-Def] ON dbo.SchedulingTemplate.PlayList = dbo.[PlayLists-Def].ID
