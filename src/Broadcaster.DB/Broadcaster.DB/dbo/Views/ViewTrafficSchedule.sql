CREATE VIEW [dbo].[ViewTrafficSchedule]
AS
SELECT     dbo.TrafficScheduleDefinition.ID, dbo.TrafficScheduleDefinition.StartingDate, dbo.TrafficScheduleDefinition.EndingDate, 
                      dbo.TrafficScheduleDefinition.Insertions, dbo.TrafficScheduleDefinition.[Value], dbo.TrafficScheduleDefinition.Type, 
                      dbo.TrafficScheduleDefinition.TypeOfValue, dbo.TrafficScheduleDefinition.Suspend, dbo.TrafficScheduleDefinition.DRM35, 
                      dbo.TrafficScheduleDefinition.StationID, dbo.TrafficScheduleDefinition.CustomerID, dbo.RadioStations.Name AS RadioName, 
                      dbo.RadioStations.DSN AS DSN, dbo.RadioStations.DB AS DB, dbo.Customers.Name AS CustomerName
FROM         dbo.TrafficScheduleDefinition INNER JOIN
                      dbo.RadioStations ON dbo.TrafficScheduleDefinition.StationID = dbo.RadioStations.ID INNER JOIN
                      dbo.Customers ON dbo.TrafficScheduleDefinition.CustomerID = dbo.Customers.ID


