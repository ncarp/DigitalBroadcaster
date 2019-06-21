

CREATE VIEW [dbo].[ViewTraffic]
AS
SELECT dbo.Traffic.ID, dbo.Traffic.BlockID, dbo.Traffic.BlockDate, 
    dbo.Traffic.Position, dbo.Traffic.SpotID, 
    Broadcaster.dbo.Spots.TypeOfBusinessID, 
    Broadcaster.dbo.Spots.MainVoiceID, dbo.ViewNBusiness.N
FROM Broadcaster.dbo.Spots INNER JOIN
    dbo.Traffic ON 
    Broadcaster.dbo.Spots.ID = dbo.Traffic.SpotID INNER JOIN
    dbo.ViewNBusiness ON 
    dbo.Traffic.BlockID = dbo.ViewNBusiness.BlockID AND 
    dbo.Traffic.BlockDate = dbo.ViewNBusiness.BlockDate AND 
    Broadcaster.dbo.Spots.TypeOfBusinessID = dbo.ViewNBusiness.TypeOfBusinessID

