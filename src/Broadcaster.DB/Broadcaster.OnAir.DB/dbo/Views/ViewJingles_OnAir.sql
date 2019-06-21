
CREATE VIEW [dbo].[ViewJingles_OnAir]
AS
SELECT dbo.JinglesOnAir.JingleID, dbo.JinglesOnAir.StartingDate, 
    dbo.JinglesOnAir.EndingDate, Broadcaster.dbo.Jingles.Name, 
    Broadcaster.dbo.Jingles.Rythm, 
    Broadcaster.dbo.Jingles.Finish - Broadcaster.dbo.Jingles.Start AS Length,
     Broadcaster.dbo.Jingles.Intro - Broadcaster.dbo.Jingles.Start AS Intro,
     Broadcaster.dbo.TypeOfJingle.Name AS JingleType, 
    Broadcaster.dbo.Jingles.TypeID
FROM dbo.JinglesOnAir INNER JOIN
    Broadcaster.dbo.Jingles ON 
    dbo.JinglesOnAir.JingleID = Broadcaster.dbo.Jingles.ID INNER JOIN
    Broadcaster.dbo.TypeOfJingle ON 
    Broadcaster.dbo.Jingles.TypeID = Broadcaster.dbo.TypeOfJingle.ID

