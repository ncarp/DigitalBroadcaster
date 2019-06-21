
CREATE VIEW [dbo].[ViewRMs_OnAir]
AS
SELECT dbo.RmsOnAir.ID, dbo.RmsOnAir.EndingDate, 
    dbo.RmsOnAir.StartingDate, dbo.RmsOnAir.RMID, 
    Broadcaster.dbo.RMs.Name, 
    Broadcaster.dbo.TypeOfRM.Name AS Type, 
    Broadcaster.dbo.RMs.TypeID, 
    Broadcaster.dbo.RMs.Finish - Broadcaster.dbo.RMs.Start AS Length
FROM Broadcaster.dbo.TypeOfRM INNER JOIN
    Broadcaster.dbo.RMs ON 
    Broadcaster.dbo.TypeOfRM.ID = Broadcaster.dbo.RMs.TypeID INNER
     JOIN
    dbo.RmsOnAir ON 
    Broadcaster.dbo.RMs.ID = dbo.RmsOnAir.RMID

