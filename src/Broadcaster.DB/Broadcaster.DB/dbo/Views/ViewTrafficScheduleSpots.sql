CREATE VIEW [dbo].[ViewTrafficScheduleSpots]
AS
SELECT     dbo.TrafficScheduleSpots.ScheduleID, dbo.TrafficScheduleSpots.[Position], dbo.TrafficScheduleSpots.SpotID, dbo.TrafficScheduleSpots.StartingDate, 
                      dbo.TrafficScheduleSpots.EndingDate, dbo.TrafficScheduleSpots.Sun, dbo.TrafficScheduleSpots.Mon, dbo.TrafficScheduleSpots.Tue, 
                      dbo.TrafficScheduleSpots.Wed, dbo.TrafficScheduleSpots.Thu, dbo.TrafficScheduleSpots.Fri, dbo.TrafficScheduleSpots.Sat, 
                      dbo.Spots.Name AS Name
FROM         dbo.TrafficScheduleSpots INNER JOIN
                      dbo.Spots ON dbo.TrafficScheduleSpots.SpotID = dbo.Spots.ID

